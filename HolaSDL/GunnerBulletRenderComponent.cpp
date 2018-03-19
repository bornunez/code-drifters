#include "GunnerBulletRenderComponent.h"
#include "GameObject.h"
#include "PlayState.h"
#include "Camera.h"
#include "Game.h"

GunnerBulletRenderComponent::GunnerBulletRenderComponent(GameObject* o) : RenderComponent(o)
{
}
void GunnerBulletRenderComponent::render()
{
	float auxX = gameObject->getTransform()->position.getX() - playState->getCamera()->getTransform()->position.getX();
	float auxY = gameObject->getTransform()->position.getY() - playState->getCamera()->getTransform()->position.getY();
	SDL_Rect rect RECT(auxX, auxY, gameObject->getTransform()->body.w, gameObject->getTransform()->body.h);
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x00055fff));
	SDL_RenderFillRect(Game::getGame()->getRenderer(), &rect);
	SDL_SetRenderDrawColor(Game::getGame()->getRenderer(), COLOR(0x00055555));
}


GunnerBulletRenderComponent::~GunnerBulletRenderComponent()
{
}
