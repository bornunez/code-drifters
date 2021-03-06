#pragma once
//#include "checkML.h"
#include "GameObject.h"
//################## ATRIBUTOS COMUNES ####################
struct CommonAttributes {
	float life;
	float maxHP;
	float speed;
	float meleeDmg; float rangedDmg;
	int minDrop; int maxDrop; //Drop de dinero
	bool stunned = false;
};
class MasterBoss:public GameObject
{
public:
	MasterBoss(int type);
	virtual ~MasterBoss();
	float getLife() { return Attributes.life; }
	float getMaxHP() { return Attributes.maxHP; };
	int getDamage() { return Attributes.meleeDmg; };
	void setLife(int life) { Attributes.life = life; };
	void setStun(bool set) { Attributes.stunned = set; }
	bool isStunned() { return Attributes.stunned; }
	virtual void death() = 0;
	virtual void changeColor(int r, int g, int b) = 0;
	int getBossType() { return type; };
protected:

	CommonAttributes Attributes;

private:
	int type;
};

