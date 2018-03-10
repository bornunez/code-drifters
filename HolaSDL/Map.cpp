#include "Map.h"
#include "Layer.h"


void Map::parseLevel()
{

}


Map::Map(string filename, Tileset* ts, Camera* camera) : filename(filename), tileset(ts),camera(camera)
{
		
}

Map::~Map()
{
}

void Map::update()
{
	for (Layer* l : layers)
		l->update();
}

void Map::render()
{
	for (Layer* l : layers)
		l->render(camera);
}

Layer * Map::GetLayer(string LayerID)
{
	for (Layer* l : layers) {
		if (l->getLayerID() == LayerID)
			return l;
	}
}