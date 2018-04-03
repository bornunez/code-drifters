#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"

class GunnerComponent :
	public UpdateComponent
{
public:
	void update();
	void receiveMessage(std::string msg) {};
	GunnerComponent(GameObject* o, GameObject* target, float dist);
	virtual ~GunnerComponent();

private:
	Vector2D gunnerPosition;
	Vector2D targetPosition;
	GameObject* targetObject;
	float velocity;
	float distancia;

};