#include "Map.h"
#include "Layer.h"


void Map::parseLevel()
{

}


Map::Map(string filename, Camera* camera) : filename(filename),camera(camera)
{
	//Inicializamos el vector para poder acceder a el
	for (int i = 0; i < 4; i++)
		doors.push_back(nullptr);
}

Map::~Map()
{
}

void Map::update()
{
	for (Layer* l : layers)
		l->update();
	for (GameObject* o : objects)
		o->update();
}

void Map::render()
{
	for (Layer* l : layers)
		l->render(camera);
	for (GameObject* o : objects)
		o->render();
}

Layer * Map::GetLayer(string LayerID)
{
	for (Layer* l : layers) {
		if (l->getLayerID() == LayerID)
			return l;
	}
}

void Map::spawn()
{
	for (Spawner* s : spawners) {
		if(s->isActive())
			s->spawn();
	}
}

Spawner::Spawner(int x, int y, EnemyType eType,bool active) : x(x), y(y), enemy(eType), active(active)
{

}
