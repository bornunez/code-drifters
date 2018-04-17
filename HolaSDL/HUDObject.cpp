#include "HUDObject.h"
#include"Texture.h"
#include "SimpleAnimationComponent.h"
#include "ResourceManager.h"

HUDObject::HUDObject(Texture* text) : GameObject(text)
{
	srcRect.x = srcRect.y = 0;
	srcRect.w = getTexture()->getFrameWidth();
	srcRect.h = getTexture()->getFrameHeight();
}

HUDObject::HUDObject() : GameObject() {

}


HUDObject::~HUDObject()
{
}
