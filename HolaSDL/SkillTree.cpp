#include "SkillTree.h"
#include "Game.h"
#include "Shop.h"
#include "ShopState.h"

#include"PlayState.h"
#include"HUDManager.h"

SkillTree::SkillTree(SkillTree* parent, string source, string TextSource, ShopState* shopSta) {
	//initial values for destRect
	shopState= shopSta;
	skill.destRect.w = skill.destRect.x = skill.destRect.h = 50;
	skill.destRect.y = 0;

	skill.text = new Texture(Game::getGame()->getRenderer());
	if (skill.text->loadFromImg(TextSource));

	parent_ = parent;
	
	shopState->createButton(this);
	ifstream archivo;
	archivo.open(source);

	int numHijos; //needed for recursion call
	archivo >> numHijos;
	//id lecture
	int i =9; //first number after "..\\Arbol\\"
	//we need to read only the number, not the "..\\Arbol\\" part
	char aux;
	string aux2;
	aux = source[i];
	while (aux != '.') {
		aux2.push_back(aux);
		i++;
		aux = source[i];
	}
	skill.id = stoi(aux2); //string to int
	archivo >> skill.bought >> skill.needed_point;
	//description lecture
	string aux3 = "";
	while (!archivo.eof()) { //End Of File
		archivo >> aux3;
		//if (aux != "") { //last
		if(!archivo.fail()){
			skill.description += aux3;
			//description_ += aux;
			skill.description.push_back(' ');//space between words
		}
	}
	archivo.close();
	
	for (int i = 1; i <= numHijos; i++) {
		//the names of the files of the sons are their ids
		AddChild(new SkillTree(this,"..\\Arbol\\"+ to_string(skill.id)+to_string(i)+".txt",
			"..\\Arbol\\Textures\\" + to_string(skill.id) + to_string(i) + ".png", shopState));
	}

	skill.HLineToFather = new Texture(Game::getGame()->getRenderer());
	skill.VLineToFather = new Texture(Game::getGame()->getRenderer());
	
	LoadLineTex();
	
}

SkillTree* SkillTree::FindSon(int n) {
	//id to recognize them
	if (n != skill.id) {
		//if different, we need to go deeper
		string aux = to_string(skill.id);
		aux += to_string(n)[aux.length()];
		//check if the son exists
		if(sons_[stoi(aux)%10 -1]!= nullptr)
			return sons_[stoi(aux)%10 -1]->FindSon(n);
		else return nullptr;
	}
	else return this;
}

void SkillTree::HandleEvents(SDL_Event e) {
	for (int i = 0; i < sons_.size(); i++) {
		//sons_[i]->boton->HandleEvents(e);
		sons_[i]->HandleEvents(e);
	}
}

void SkillTree::render(SDL_Rect destination, int size, int totalWidth ) {
	if (parent_ == nullptr) {
		skill.destRect.x = destination.x + destination.w / 5;
		skill.destRect.y = destination.y + destination.h / 10;
		skill.destRect.w = destination.w - ((skill.destRect.x - destination.x) * 2);
		skill.destRect.h = skill.destRect.w / 2;
	}
	else {
		skill.destRect.w = skill.destRect.h = size;
		skill.destRect.x = destination.x - skill.destRect.w / 2 + totalWidth / 2 + totalWidth/30;
		skill.destRect.y = parent_->skill.destRect.y + (parent_->skill.destRect.h) + (skill.destRect.h * (destination.h >= 450 ? 0.9 : 2));
	}

	DrawLine();
	if (parent_ != nullptr && parent_->parent_ == nullptr)
		parent_->skill.text->render(parent_->skill.destRect);
	skill.text->render(skill.destRect);

	if (sons_.size() > 0) {
		
		if (sons_.size() > 1)
			destination.x -= (destination.w / (sons_.size() * 2));
		//destination.x += destination.w / sons_.size();
		destination.w = destination.w / sons_.size();
		for (int i = 0; i < sons_.size(); i++)
		{
			sons_[i]->render(destination, size, totalWidth);
			destination.x += (destination.w);
			if(parent_ == nullptr)
				destination.x -=(size/2);
		}
	}
}

SDL_Rect SkillTree::GetSkillRect()
{
	return skill.destRect;
}

void SkillTree::Buy() {
	if (parent_ != nullptr && !skill.bought && parent_->Unlocked() && PlayState::getInstance()->getMainCharacter()->getMoney() >= skill.needed_point) {
		skill.bought = true;
		PlayState::getInstance()->getMainCharacter()->changeMoney(-skill.needed_point);
		skill.needed_point = -1;
		UpdateBox();
		LoadLineTex();
		effect();
	}
	}

void SkillTree::UpdateBox()
{
	if (parent_ == nullptr) {
		shopState->updateBox(skill.description, skill.needed_point);
	}
	else {
		if (parent_->Unlocked()) {
			shopState->updateBox(skill.description, skill.needed_point);
		}
		else { shopState->updateBox(skill.description, 0); }
	}
		shopState->activeBox(true);
	
}

void SkillTree::DesactiveBox()
{
	shopState->activeBox(false);
}

string SkillTree::FindParentID() {
	if (parent_ != nullptr)
		return to_string(parent_->skill.id);
	else return "";
}

int SkillTree::TreeHeight() {
	//minimun height, only a root
	int height = 1;
	//if (parent_ != nullptr)
		//return parent_->TreeHeight();
	//else {
		if (sons_.size() > 0) {
			//the height of the first son
			int aux = sons_[0]->TreeHeight();
			for (int i = 1; i < sons_.size(); i++) {
				int aux2 = sons_[i]->TreeHeight();
				//check which son has the highest height
				if (aux < aux2)
					aux = aux2;
			}
			//minimum + height of the son
			height += aux;
		}
	//}
	return height;
}

void SkillTree::DrawLine() {
	if (parent_ != nullptr) {
		SDL_Rect auxRect;
		//horizontal line first

		//middle point of the father
		auxRect.y = parent_->skill.destRect.y + parent_->skill.destRect.h / 2;
		if (skill.destRect.x < parent_->skill.destRect.x)
			auxRect.x = skill.destRect.x + (skill.destRect.w / 2) - skill.destRect.h / 8;
		else auxRect.x = parent_->skill.destRect.x + (parent_->skill.destRect.w);

		auxRect.h = skill.destRect.h/4;	//just a designed measure
		if(parent_->parent_ != nullptr)	//not a son of the root, because they have no horizontal line
			auxRect.w = abs(skill.destRect.x - parent_->skill.destRect.x) - parent_->skill.destRect.w / 2 + skill.destRect.h /8;
		else auxRect.w = 0;	//if it is a son of the root

		auxRect.y -= (auxRect.h / 2); //to adjust to right the center

		skill.HLineToFather->render(auxRect);
		auxRect.y += auxRect.h / 2;
		//now vertical line
		if (auxRect.w <= 0) {
			auxRect.h = skill.destRect.y - parent_->skill.destRect.y - parent_->skill.destRect.h;
			/*if (parent_->parent_ == nullptr)
				auxRect.h = auxRect.h / 2;*/
			auxRect.y += parent_->skill.destRect.h / 2;
		}
		else auxRect.h = skill.destRect.y - parent_->skill.destRect.y;
		auxRect.w = skill.destRect.w/4;

		auxRect.x = skill.destRect.x + (skill.destRect.w/2) - auxRect.w/2;

		skill.VLineToFather->render(auxRect);
	}
}

void SkillTree::LoadLineTex()
{
	if (!skill.bought) {
		if (skill.HLineToFather->loadFromImg("..\\Arbol\\Textures\\Line.png"));
		if (skill.VLineToFather->loadFromImg("..\\Arbol\\Textures\\Line.png"));
	}
	else {
		//int TreeNumber = to_string(skill.id).front() - '0';
		int TreeNumber = getRootID();
		switch (TreeNumber)
		{
		case 1:
			if (skill.HLineToFather->loadFromImg("..\\Arbol\\Textures\\RedLine.png"));
			if (skill.VLineToFather->loadFromImg("..\\Arbol\\Textures\\RedLine.png"));
			break;
		case 2:
			if (skill.HLineToFather->loadFromImg("..\\Arbol\\Textures\\BlueLine.png"));
			if (skill.VLineToFather->loadFromImg("..\\Arbol\\Textures\\BlueLine.png"));
			break;
		case 3:
			if (skill.HLineToFather->loadFromImg("..\\Arbol\\Textures\\GreenLine.png"));
			if (skill.VLineToFather->loadFromImg("..\\Arbol\\Textures\\GreenLine.png"));
		default:
			break;
		}
	}
}

int SkillTree::getRootID() {
	if (parent_ == nullptr)
		return skill.id;
	else return parent_->getRootID();
}

void SkillTree::effect() {
	MainCharacter* character = PlayState::getInstance()->getMainCharacter();
	switch (skill.id)
	{
	case 11:
		character->addPercentualDamage((float)100/(float)3);
		break;
	case 111:
		character->addPercentualDamage(50);
		break;
	case 22:
		character->setMaxBullets(character->getMaxBullets() + 1);
		HUDManager::getInstance()->addBullet();
		break;
	case 221:
		character->setReloadTime(character->getReloadTime() * 0.67);
		break;
	case 31:
		//add a bonus 10% max HP
		character->addMaxHP(character->getMaxHP() / 10);
		break;
	default:
		break;
	}
}