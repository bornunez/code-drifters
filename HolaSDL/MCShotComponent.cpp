#pragma once
#include "MCShotComponent.h"
#include "Bullet.h"
#include "ResourceManager.h"
#include "PlayState.h"
#include "GameState.h"
#include "MCBulletComponent.h"
#include "MCBulletRenderComponent.h"
#include "MainCharacter.h"
#include "Camera.h"
#include "PlayState.h"
#include <iostream>
#include "BulletManager.h"


MCShotComponent::MCShotComponent(GameObject * o) : InputComponent(o)
{
	this->bulletManager = bulletManager;
	this->lastReloadTime = new Timer();
}

MCShotComponent::~MCShotComponent()
{
}

void MCShotComponent::handleEvents(SDL_Event & e)
{
	int currentBullets = dynamic_cast<MainCharacter*>(gameObject)->getCurrentBullets();
	int reloadTime = dynamic_cast<MainCharacter*>(gameObject)->getReloadTime();//Tiempo para que se recargue una bala
	int maxBullets = dynamic_cast<MainCharacter*>(gameObject)->getMaxBullets();
	lastReloadTime->update();

	if (currentBullets == maxBullets) {//Si el cargador est� al m�ximo la recarga se mantiene en pausa
		lastReloadTime->restart();
	}
	if (lastReloadTime->TimeSinceTimerCreation > reloadTime) {//Si el tiempo desde la �ltima recarga supera al tiempo de recarga del personaje
		if (currentBullets < maxBullets) {//Suma una bala si el cargador no est� lleno
			currentBullets++;
			dynamic_cast<MainCharacter*>(gameObject)->setCurrentBullets(currentBullets);
			lastReloadTime->restart();//Reinicia el tiempo desde la �ltima recarga
		}
	}
	if (e.button.button == SDL_BUTTON_RIGHT && e.type == SDL_MOUSEBUTTONDOWN) {
		if (currentBullets > 0) {//Si tiene balas en el cargador dispara
			int mouseX, mouseY;
			SDL_Point p;
			SDL_Rect r;
			SDL_GetMouseState(&p.x, &p.y);
			aux.setX(p.x);
			aux.setY(p.y);//Posici�n del cursor en pantalla


			//Cambia la posici�n de donde sala la bala, es temporal hasta que tengamos los frames de la animaci�n definidos
			Vector2D gunPosition;
			gunPosition.setX(getGameObject()->getTransform()->position.getX() + getGameObject()->getTransform()->body.w / 2);
			gunPosition.setY(getGameObject()->getTransform()->position.getY() + getGameObject()->getTransform()->body.h / 2);
			dynamic_cast<MainCharacter*>(gameObject)->setGunPosition(gunPosition);
			
			Transform bulletTransform;
			bulletTransform.position = gunPosition;
			bulletTransform.body.w = bulletTransform.body.h = 10;


			Vector2D displayPosition;//Posici�n del personaje relativa a la c�mara
			displayPosition = (gunPosition - PlayState::getInstance()->getCamera()->getTransform()->position);
			bulletTransform.direction = aux - displayPosition;//Resta la posici�n del cursor al del personaje
			bulletTransform.direction.normalize();//Halla el vector de direcci�n 
			bulletTransform.velocity = bulletTransform.direction;
			bulletTransform.speed = 1000.0;

			BulletManager::getInstance()->shoot(this->gameObject, bulletTransform, BulletType::MCBullet);

			//Crea la bala y le pasa el transform
			//Bullet* auxBullet = new Bullet(ResourceManager::getInstance()->getTexture(BulletSprite), bulletTransform, true);

			//Le a�ade los componentes de f�sicas y render
			//auxBullet->addComponent(new MCBulletComponent(auxBullet, 1.5));
			//auxBullet->addComponent(new MCBulletRenderComponent(auxBullet));
			//A�ade la bala a los objetos de la sala actual
			//PlayState::getInstance()->addGameObject(auxBullet);

			currentBullets--;//Le resta balas al personaje
			static_cast<MainCharacter*>(gameObject)->setCurrentBullets(currentBullets);
		}
	}


}
