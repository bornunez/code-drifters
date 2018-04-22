#include "Boss.h"
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

using namespace std;
Boss::Boss(Transform t) : MasterBoss()
{
	transform.position.setX(t.position.getX());
	transform.position.setY(t.position.getY());
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
}

Boss::Boss(MainCharacter* prot, int x, int y, int w, int h) : MasterBoss()
{

	transform.position.setX(x);
	transform.position.setY(y);
	transform.body.w = w;
	transform.body.h = h;
	prota = prot;
	posInic = Vector2D(transform.position.getX(), transform.position.getY());
	vida = 500;
	da�o = 10;
	allUpdates();
	loadAnimations();
	this->changeCurrentAnimation("CANSADO");

	rend = new RenderBoss(this);
	addComponent(rend);
	updat = new UpdateBoss(this, prota);
	addComponent(updat);

    BoxRenderer* skel = new BoxRenderer(this, playState->getCamera());
	addComponent(skel);
}
Boss::~Boss()
{
}



void Boss::loadAnimations()
{
	Tileset* tileset = ResourceManager::getInstance()->getBoss1Tileset(0);
	string animationPath = "../Animations/Bosses/Boss1/Boss1.tmx";

	//Animaciones
	Animation* desvanece = AnimationParser::parseAnimation(tileset, animationPath, "Desvanece", this, 25, 0, false, 0.1);
	Animation* aparece = AnimationParser::parseAnimation(tileset, animationPath, "Aparece", this, 0, 0, false, 0.05);
	Animation* cansado = AnimationParser::parseAnimation(tileset, animationPath, "Cansado", this, 0, -75, true, 0.1);
	Animation* startJump = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-StartJump", this, 0, -75, false, 0.1);
	Animation* startAttackJump = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-StartAttackJump", this, 0, 0, false, 0.1);
	Animation* staticJump = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-StaticJump", this, 0, 0, true, 0.1);
	Animation* normalFall = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-NormalFall", this, 0, -75, false, 0.1);
	Animation* attackFall = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-AttackFall", this, 0, -75, false, 0.1);
	Animation* estatico = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-Static", this, 0, -75, true, 0.1);
	Animation* attack = AnimationParser::parseAnimation(tileset, animationPath, "Boss1-NormalAttack", this, 0, 0, false, 0.1);


	//Nombres de animaciones
	animations.emplace("DESVANECE", desvanece);
	animations.emplace("CANSADO", cansado);
	animations.emplace("APARECE", aparece);
	animations.emplace("START_JUMP", startJump);
	animations.emplace("START_ATTACK_JUMP", startAttackJump);
	animations.emplace("STATIC_JUMP", staticJump);
	animations.emplace("NORMAL_FALL", normalFall);
	animations.emplace("ATTACK_FALL", attackFall);
	animations.emplace("STATIC", estatico);
	animations.emplace("NORMAL_ATTACK", attack);
}

