#include "StunComponent.h"
#include "Enemy.h"
#include <iostream>
#include "Animation.h"

StunComponent::StunComponent(GameObject * o) : UpdateComponent(o)
{
	enemy = static_cast<Enemy*>(gameObject);
	stunTime = 0;
}


StunComponent::~StunComponent()
{
}

void StunComponent::update()
{
	stunTimer.update();
	//Si esta stunneado, lo activamos cuando pase el tiempo de stun
	if (enemy->isStunned() && (stunTimer.TimeSinceTimerCreation > stunTime))
	{
		stunTimer.restart();
		enemy->getCurrentAnimation()->changeColor(255, 255, 255);
		enemy->setStun(false);
		std::cout << "Ya no estoy stuneado" << std::endl;
	}
}

void StunComponent::receiveMessage(Message * msg)
{
	switch (msg->id)
	{
	case MC_BULLET_COLLISION: {
		if (!enemy->isStunned()) {
			stunTime = static_cast<MCBulletStun*>(msg)->stunTime;
			stunTimer.restart();
			enemy->getCurrentAnimation()->changeColor(0, 0, 200);
			enemy->setStun(true);
			std::cout << "AAAAAA QUE ME ATURDEN CO�O ES DESESPERANTEEEEE" << std::endl;
		}
	}
	default:
		break;
	}
}
