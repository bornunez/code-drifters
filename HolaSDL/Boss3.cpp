#include "Boss3.h"
#include "Game.h"
#include "Camera.h"
#include "MainCharacter.h"
#include "Timer.h"
#include "Time.h"
#include "Vector2D.h"
#include "Bullet.h"
#include "ResourceManager.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "BoxRenderer.h"
#include "DamageableBossComponent.h"

using namespace std;
Boss3::Boss3(Transform t) : MasterBoss(2)
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
}

Boss3::Boss3(MainCharacter* prot, int x, int y, int w, int h) : MasterBoss(3)
{
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w/1.5f;
	transform.body.h = h*1.1f;
	transform.body.w = w;
	transform.body.h = h;
	setSpriteOffset(1 * Game::getGame()->getScale(), -8 * Game::getGame()->getScale());

	transform.overlapCollision.overlapBody.w = w/1.25f;
	transform.overlapCollision.overlapBody.h = h;
	transform.overlapCollision.overlapOffset.setX(5);
	transform.overlapCollision.overlapOffset.setY(0);

	prota = prot;
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
	Attributes.life = 2000;
	Attributes.maxHP = Attributes.life;
	Attributes.meleeDmg = 8;
	allUpdates();
	loadAnimations();
	this->changeCurrentAnimation("STATIC_UP");

	updat = new UpdateBoss3(this, prota);
	addComponent(updat);
	rend = new RenderBoss3(this);
	addComponent(rend);
	addComponent(new DamageableBossComponent(this, prota, 0.2));
	addComponent(new SkeletonRendered(this, playState->getCamera()));


	//BoxRenderer* skel = new BoxRenderer(this, playState->getCamera());
	//addComponent(skel);

}
Boss3::~Boss3()
{
}



void Boss3::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getBoss3Tileset(0);
	string animationPath = "../Animations/Bosses/Boss3/Boss3.tmx";

	//Animaciones
	Animation* abreBrazos = AnimationParser::parseAnimation(tileset, animationPath, "AbreBrazos", this, 0, 0, false, 0.04);
	Animation* carga = AnimationParser::parseAnimation(tileset, animationPath, "Carga", this, 0, 0, false, 0.1);
	/*Animation* warning = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-Warning", this, 0, 0, true, 0.1);
	Animation* sacaRayos = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-SacaRayos", this, 0, 0, false, 0.1);
	Animation* entra = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-Entra", this, 0, 0, false, 0.1);
	Animation* staticDown = AnimationParser::parseAnimation(tileset, animationPath, "Boss2-StaticDown", this, 0, 0, true, 0.1);
	*/
	//Nombres de animaciones
	animations.emplace("ABRE_BRAZOS", abreBrazos);
	animations.emplace("CARGA", carga);
	/*
	animations.emplace("WARNING", warning);
	animations.emplace("SACA_RAYOS", sacaRayos);
	animations.emplace("ENTRA", entra);
	animations.emplace("STATIC_DOWN", staticDown);
	*/
}

void Boss3::changeColor(int r, int g, int b)
{
	updat->changeColor(255, 100, 100);
}

void Boss3::updateEnemies()
{
	for (int i = 0; i < wheels.size(); i++)
	{
		if (wheels[i] != nullptr)
		{
			wheels[i]->update();
		}
	}
}

void Boss3::renderEnemies()
{
	for (int i = 0; i < wheels.size(); i++)
	{
		if (wheels[i] != nullptr)
		{
			wheels[i]->render();
		}
	}
}
void Boss3::createWheel(int posX, int posY, float velocidad, int dir)
{
	int i = 0;
	bool pulled = false;
	while (i < wheels.size() && !pulled)
	{
		if (!wheels[i]->isActive())
		{
			wheels[i] = new Wheel(prota, posX, posY, 50, 50, velocidad, dir);
			pulled = true;
		}
		i++;
	}
	if (i == wheels.size())
	{
		wheels.push_back(new Wheel(prota, posX, posY, 50, 50, velocidad, dir));
	}
}