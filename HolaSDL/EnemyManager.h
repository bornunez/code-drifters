#pragma once
#include <vector>
#include <list>

using namespace std;
class Enemy;
class MainCharacter;

enum EnemyType{Stalker, Gunner, Ninja};
struct EnemyParams {
	int life;
	int speed;
	int meleDmg; int rangedDmg;
	int minDrop; int maxDrop;
};

class EnemyManager
{
private:
	const int nEnemies = Ninja - Stalker;
	//Singleton things
	EnemyManager();
	static EnemyManager* instance;
	//Donde van a estar los datos por defecto de los enemigos (Lo suyo seria leerlo de un XML )
	vector<EnemyParams> eParams = { {100,10,10,0,5,7},{75,10,5,10,7,8},{75,15,15,0,7,8} };
	//Donde van a estal almacenados todos los enemigos del juego
	list<Enemy*> inactives;
	list<Enemy*> actives;

	//Metodo aux para coger un enemigo del vector de inactivos, Coste O(n) con n = numero de enemigos inactivos
	Enemy* createEnemy(EnemyType eType);
	Enemy* getInactiveEnemy(EnemyType eType);

	MainCharacter* mc;

public:
	~EnemyManager();
	static EnemyManager* getInstance();
	void update();
	void render();

	EnemyParams getParams(EnemyType type) { return eParams[type]; }

	//Spawnea un tipo de enemigo en unas X, Y dadas
	void spawn(int x, int y, EnemyType eType);
	//Desactiva un enemigo
	void kill(Enemy* enemy);
	//Inicializar el Manager. Llamar al principio
	void init(MainCharacter* mainCharacter);

};

