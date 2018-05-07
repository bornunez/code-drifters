#include "BombComponent.h"
#include "GameObject.h"
#include "Bullet.h"
#include "GunnerBulletComponent.h"
#include "GunnerBulletRenderComponent.h"
#include "Game.h"
#include "PlayState.h"
#include "ResourceManager.h"
#include "EnemyBomb.h"
#include "Camera.h"


BombComponent::BombComponent(GameObject* o, int bulletsNumber, float time, float speed)
	: UpdateComponent(o)
{
	eb = static_cast<EnemyBomb*>(gameObject);
	nBullets = bulletsNumber;
	explodeTime = time;
	bombTimer = new Timer();
	bombSpeed = speed;
}

BombComponent::~BombComponent()
{
}


void BombComponent::handleAnimation()
{
	
}




void BombComponent::explode() {
	if (bombTimer->TimeSinceTimerCreation > explodeTime) {
		bombTimer->restart();
		cout << "kabom";
		Transform bulletTransform;
		bulletTransform.body.w = 50;
		bulletTransform.body.h = 15;
		bulletTransform.position.set(gameObject->getCenterPos().getX() - bulletTransform.body.w / 2, gameObject->getCenterPos().getY() - bulletTransform.body.h / 2);
		
		for (int i = 0; i < nBullets; i++) {
			Vector2D auxVel(0, 1);
			auxVel.rotate((360/nBullets) * (i - 1));
			auxVel.normalize();
			bulletTransform.velocity = bulletTransform.direction = auxVel;
			bulletTransform.speed = bombSpeed;

			BulletManager::getInstance()->shoot(this->gameObject, bulletTransform, BulletType::GunnerBullet);
		}
		eb->death();
	}

}

void BombComponent::update() {
	if (!gameObject->isDead()) {
		bombTimer->update();
		explode();
		handleAnimation();
	}
}