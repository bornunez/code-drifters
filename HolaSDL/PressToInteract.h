#pragma once
#include "RenderComponent.h"
class PressToInteract :
	public RenderComponent
{
public:
	PressToInteract(GameObject* o);
	virtual ~PressToInteract();
	void lateRender();
};
