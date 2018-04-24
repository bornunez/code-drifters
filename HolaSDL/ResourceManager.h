#pragma once
#include "Texture.h"
#include <vector>
class Tileset;

// CONSTANTES
const int NUM_TEXTURES = 71;
const int NUM_TILESET = 1;
const int NUM_PROTATILESET = 1;
const int NUM_ENEMYTILESET = 4;
const int NUM_BOSS1TILESET = 1;
const string TEXT_PATH = "..\\images\\";
const string LEVEL_PATH = "..\\levels&tiles\\";
const string TILESET_PATH = "..\\levels&tiles\\";
const string ENEMY_PATH = "..\\Animations\\Enemies\\";
const string PROTATILESET_PATH = "..\\Animations\\Protagonist\\tileset\\";
const string BOSS1_PATH = "..\\Animations\\Bosses\\Boss1\\";
// Estructura para las texturas
typedef struct {
	string filename;
	int numRows;
	int numCols;
} TextureAtributes;

//Aqui se pone el nombre que se le va a dar  a la textura como argumento en el getTexture
enum TextureId {
	MCBullet, MCGun, GunnerBullet, HookChain, HookChainFail, HookHead, Blood, GunnerBulletExplosion, LifeBarra, LifeBorde, LifeFondo,
	UltBorde, UltBarra, UltFondo, HUDBulletBarra, HUDBulletFondo, HUDBulletBorde,

	//TEXTURAS DEL MINIMAPA
	MinimapBorder, MinimapBase, //Borde
	BaseRoom, //Todas las bases
	First_On,First_Off,Normal_On,Normal_Off,Boss_On,Boss_Off, Shop_On,Shop_Off, Chest_On,Chest_Off,
	//Todas las puertas abiertas
	OpenUp, OpenRight, OpenDown, OpenLeft,
	OpenUpNormalOn, OpenRightNormalOn, OpenDownNormalOn, OpenLeftNormalOn,
	OpenUpNormalOff, OpenRightNormalOff, OpenDownNormalOff, OpenLeftNormalOff,
	//Todas las puertas cerradas
	ClosedUp, ClosedRight, ClosedDown, ClosedLeft,

	OneCoinSprite, FiveCoinSprite,TenCoinSprite,
	SwordButton, GunButton, MemexButton, MaxAttackButton, SwordChargeButton,
};

//IMPORTANTE//
//El orden en el que se ponen las cosas en la enum debe ser el mismo que en el que se a�aden las cosas abajo en TextureAtributes ya que si no no van a coincidir

using namespace std;
class ResourceManager
{
private:
	//Aqui se a�aden las texturas con estoso args {path, numRows, numCols}
	const TextureAtributes TEXTURE_ATRIBUTES[NUM_TEXTURES]{
		{ "MCBullet.png", 1, 1 },
		{"GunRight.png",1,1},
		{ "GunnerBullet.png", 1, 5 },
		{ "HookChain.png", 1,2},
		{"HookChainFail.png",2,13},
		{"HookHead.png", 1 ,2},
		{"Particles\\Blood.png", 3, 3},
		{ "Particles\\GunnerBulletExplosion.png", 2, 7 },
		{"Interfaz\\Barra.png", 1, 1},
		{"Interfaz\\Borde.png", 1, 1},
		{"Interfaz\\Fondo.png",1,1},
		{"Interfaz\\BordeUlt.png", 1, 1},
		{"Interfaz\\BarraUlt.png",1, 1},
		{"Interfaz\\FondoUlt.png", 1, 1},
		{"Interfaz\\BalaBarra2.png", 1, 1},
		{"Interfaz\\BalaFondo2.png", 1, 1},
		{"Interfaz\\BalaBorde2.png", 1, 1},

		//MINIMAPA
		{"Interfaz\\Minimapa\\MinimapBorde.png",1,1},
		{ "Interfaz\\Minimapa\\MinimapBase.png",1,1 },
		{ "Interfaz\\Minimapa\\BaseRoom.png",1,1 },
		//Los rellenos
		{ "Interfaz\\Minimapa\\First_On.png",1,1 },
		{ "Interfaz\\Minimapa\\First_Off.png",1,1 },
		{ "Interfaz\\Minimapa\\Normal_On.png",1,1 },
		{ "Interfaz\\Minimapa\\Normal_Off.png",1,1 },
		{ "Interfaz\\Minimapa\\Boss_On.png",1,1 },
		{ "Interfaz\\Minimapa\\Boss_Off.png",1,1 },
		{ "Interfaz\\Minimapa\\Shop_On.png",1,1 },
		{ "Interfaz\\Minimapa\\Shop_Off.png",1,1 },
		{ "Interfaz\\Minimapa\\Chest_On.png",1,1 },
		{ "Interfaz\\Minimapa\\Chest_Off.png",1,1 },
		//Open
		{ "Interfaz\\Minimapa\\OpenUp.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenRight.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenDown.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenLeft.png",1,1 },

		{ "Interfaz\\Minimapa\\OpenUpNormalOn.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenRightNormalOn.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenDownNormalOn.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenLeftNormalOn.png",1,1 },

		{ "Interfaz\\Minimapa\\OpenUpNormalOff.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenRightNormalOff.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenDownNormalOff.png",1,1 },
		{ "Interfaz\\Minimapa\\OpenLeftNormalOff.png",1,1 },
		//Closed
		{ "Interfaz\\Minimapa\\ClosedUp.png",1,1 },
		{ "Interfaz\\Minimapa\\ClosedRight.png",1,1 },
		{ "Interfaz\\Minimapa\\ClosedDown.png",1,1 },
		{ "Interfaz\\Minimapa\\ClosedLeft.png",1,1 },


		{ "coin.png", 1, 4},
		{ "coin_five.png", 1, 4 },
		{ "coin_ten.png", 1, 4 },

		{ "Tree\\1.png", 1, 1 },
		{ "Tree\\2.png", 1, 1 },
		{ "Tree\\3.png", 1, 1 },
		{ "Tree\\11.png", 1, 1 },
		{ "Tree\\12.png", 1, 1 },
		{ "Tree\\21.png", 1, 1 },
		{ "Tree\\22.png", 1, 1 },
		{ "Tree\\31.png", 1, 1 },
		{ "Tree\\32.png", 1, 1 },
		{ "Tree\\111.png", 1, 1 },
		{ "Tree\\121.png", 1, 1 },
		{ "Tree\\122.png", 1, 1 },
		{ "Tree\\211.png", 1, 1 },
		{ "Tree\\221.png", 1, 1 },
		{ "Tree\\311.png", 1, 1 },
		{ "Tree\\312.png", 1, 1 },
		{ "Tree\\321.png", 1, 1 },
		{ "Tree\\2211.png", 1, 1 },
		{ "Tree\\BlueLine.png", 1, 1 },
		{ "Tree\\GreenLine.png", 1, 1 },
		{ "Tree\\RedLine.png", 1, 1 },
		{ "Tree\\Line.png", 1, 1 },
	};



	//Array que contiene punteros a todas las texturas del juego.
	Texture* textures[NUM_TEXTURES];
	//Vector de tilesets
	vector<Tileset*> tilesets;
	const string protaTilesetName = "ProtaAnimation.tsx";
	Tileset* protaTileset;
	const string boss1TilesetNames[NUM_BOSS1TILESET]{ "Boss1.tsx" };
	const string enemyTilesetNames[NUM_ENEMYTILESET]{ "Gunner.tsx", "Stalker.tsx", "Torreta.tsx", "Charger.tsx" };
	vector<Tileset*> enemyTilesets;
	vector<Tileset*> boss1Tilesets;
	SDL_Renderer* renderer;
	static ResourceManager* instance;

	void loadTextures();
	Tileset* loadTileset(string path);
	void loadProtaTileset();
	void loadEnemyTilesets();
	void loadBoss1Tilesets();
	ResourceManager(SDL_Renderer* renderer);

public:
	static ResourceManager* getInstance() { return instance; }
	static void createInstance(SDL_Renderer* renderer);

	~ResourceManager();

	//Devuelve la textura dado su numero en la enum
	Texture * getTexture(TextureId id);
	Tileset* getTileset(string path);
	Tileset* getProtaTileset() { return protaTileset; };
	Tileset* getEnemyTileset(int numTileset) { return enemyTilesets[numTileset]; };
	Tileset* getBoss1Tileset(int numTileset) { return boss1Tilesets[numTileset]; };
	string getLevelPath() { return LEVEL_PATH; };
};

