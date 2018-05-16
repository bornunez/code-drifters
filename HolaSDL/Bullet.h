#pragma once
#include "checkML.h"
#include "GameObject.h"

//Tipo de la bala
enum class BulletType { MCBullet, GunnerBullet, TurretBullet};
class Bullet : public GameObject
{
private:
	BulletType type;
	float angle;
public:
	Bullet(Texture * tex, bool active, BulletType type);
	Bullet(Texture * tex, Transform t, bool active, BulletType type);
	Bullet(Texture * tex, int x, int y, int width, int height, bool active, BulletType type);
	BulletType getType(){ return type; }
	virtual ~Bullet();

	float getAngle() { return angle; }
	void setAngle(float a) { angle = a; }
};