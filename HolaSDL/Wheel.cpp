#include "Wheel.h"
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
#include "BasicInvincibleComponent.h"

using namespace std;
Wheel::Wheel(Transform t) : Enemy(prota)
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
}

Wheel::Wheel(MainCharacter* prot, int x, int y, int w, int h) : Enemy(prot)
{
	prota = prot;
	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	allUpdates();
	loadAnimations();
	Attributes.defense = 30;
	this->changeCurrentAnimation("SALE");
	this->getCurrentAnimation()->startAnimation();

	updat = new UpdateWheel(this, prota);
	addComponent(updat);
	rend = new RenderWheel(this);
	addComponent(rend);


	BoxRenderer* skel = new BoxRenderer(this, playState->getCamera());
	addComponent(skel);
	addComponent(new BasicInvincibleComponent(this, 0.2));
}
Wheel::~Wheel()
{
}



void Wheel::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getBoss1Tileset(0);
	string animationPath = "../Animations/Enemies/Wheel/Wheel.tmx";

	//Animaciones
	Animation* sale = AnimationParser::parseAnimation(tileset, animationPath, "Wheel-Sale", this, 0, 0, false, 0.1);
	Animation* gira = AnimationParser::parseAnimation(tileset, animationPath, "Wheel-Gira", this, 0, 0, true, 0.1);
	Animation* entra = AnimationParser::parseAnimation(tileset, animationPath, "Wheel-Entra", this, 0, 0, false, 0.1);
	

	//Nombres de animaciones
	animations.emplace("SALE", sale);
	animations.emplace("GIRA", gira);
	animations.emplace("ENTRA", entra);
	
}


void Wheel::death()
{
	map<const char*, Animation*>::iterator it;
	for (it = animations.begin(); it != animations.end(); it++)
	{
		it->second->changeColor(0, 0, 0);
	}
}

void Wheel::changeColor(int r, int g, int b)
{
	updat->changeColor(255, 100, 100);
}