#include <tmx/Layer.h>
#include <tmx/TileLayer.h>
#include <tmx/ImageLayer.h>
#include <tmx/ObjectLayer.h>
#include <tmx/Map.h>

using namespace tmx;

Layer::Layer()
: _map(nullptr)
{
}

Map*Layer::map() const
{
	return _map;
}

void Layer::setMap(Map* map)
{
	_map = map;
}

bool Layer::isTileLayer() const
{
	return false;
}

bool Layer::isImageLayer() const
{
	return false;
}

bool Layer::isObjectLayer() const
{
	return false;
}

TileLayer* Layer::asTileLayer()
{
	return dynamic_cast<TileLayer*>(this);
}

ImageLayer* Layer::asImageLayer()
{
	return dynamic_cast<ImageLayer*>(this);
}

ObjectLayer* Layer::asObjectLayer()
{
	return dynamic_cast<ObjectLayer*>(this);
}
