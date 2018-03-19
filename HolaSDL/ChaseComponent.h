#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"

class ChaseComponent :
	public UpdateComponent
{
public:
	void update();
	void recieveMessage(std::string msg) {};
	ChaseComponent(GameObject* o, GameObject* target);
	virtual ~ChaseComponent();

private:
	GameObject* targetObject;
	float angle;
};

