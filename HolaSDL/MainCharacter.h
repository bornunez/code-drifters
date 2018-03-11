#pragma once
#include "PlayStateObject.h"
#include "Animation.h"
#include <map>
class PlayState;


class MainCharacter : public PlayStateObject
{
private:
	int currentRoomX;
	int currentRoomY;
	float HP;
	float velocity;
	float maxVelocity;
	float meleeDamage;
	bool activeHook;
	bool firingGun;
	bool attacking;
	int maxBullets;
	int currentBullets;
	int reloadTime;
	Vector2D gunPosition;//Posici�n de donde sale la bala
	std::map<const char*, Animation*> animations;
	Animation* currentAnimation;
	Animation* walkLeft;
	Animation* walkRight;

public:

	MainCharacter(PlayState* playState, Game* game, Texture* tex, int x, int y, int w, int h);

	~MainCharacter();
	
	//Animations
	void createAnimations();

	//Getters & Setters
	void setCurrentBullets(int num);
	int getCurrentBullets();
	void setMaxBullets(int bullets);
	int getMaxBullets();
	float getMeleeDamage();
	void setMeleeDamage(float dmg);
	void setMaxVelocity(float vel);
	float getVelocity();
	float getMaxVelocity();
	float getHP();
	Vector2D getGunPosition();
	void setGunPosition(Vector2D pos);
	void substractHP(int damage);
	int getCurrentRoomX();
	int getCurrentRoomY();
	void changeCurrentRoom(int x, int y);
	int getReloadTime();
	void setReloadTime(int miliseconds);
};


