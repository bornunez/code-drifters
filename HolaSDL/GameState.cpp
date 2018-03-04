#pragma once
#include "GameState.h"


void GameState::cleanGarbage()
{
	while (!garbage.empty()) 
	{
		GameObject* aux=garbage.front();
		garbage.pop();
		if (aux != nullptr) 
		{
			gameObjects.remove(aux);
		}
	}
}

GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::addGameObject(GameObject * go)
{
	gameObjects.push_back(go);
}

void GameState::removeGameObject(GameObject * go)
{
	garbage.push(go);
}


