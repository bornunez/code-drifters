#pragma once
#include "Enemy.h"
#include "Game.h"
#include "Camera.h"
#include "Transform.h"
#include "MainCharacter.h"
#include "PlayState.h"
#include "GameObject.h"
#include "Managers.h"
#include "Map.h"

Enemy::Enemy(MainCharacter* mc) : GameObject()
{
	this->mainCharacter = mc;
	transform.position.set(10, 10);
	//this->addComponent(new ChaseComponent(this, mainCharacter, 0.1));
}

Enemy::~Enemy()
{
}

void Enemy::spawn(int x, int y, Spawner* spawner)
{
	//Lo spawneamos en la posicion que digan
	transform.position.setX(x); transform.position.setY(y);
	transform.body.x = x; transform.body.y = y;

	//Y ponemos sus valores por defecto
	EnemyParams params = GameManager::getInstance()->getEnemyManager()->getParams(type);
	life = params.life; 
	transform.speed = params.speed;
	meleeDmg = params.meleDmg; rangedDmg = params.rangedDmg ;
	minDrop = params.minDrop; maxDrop = params.maxDrop;
	this->spawner = spawner;
}

void Enemy::render() {
	GameObject::render();
}

void Enemy::update()
{
	GameObject::update();
}

GameObject* Enemy::getMC() {
	return mainCharacter;
}


void Enemy::receiveDamage(int damage) {
	life -= damage;
	if (life <= 0) {
		onDestroy();
	}
}

void Enemy::onDestroy() {
	//Si tenemos un spawner asignado, nos destruimos
	if(spawner != nullptr)
		spawner->setActive(false);
	//droppear dinero etc
	GameManager::getInstance()->getEnemyManager()->kill(this);
}
