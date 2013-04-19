#include <tmx/Layer.h>
#include <tmx/TileLayer.h>
#include <tmx/ImageLayer.h>
#include <tmx/ObjectLayer.h>
#include <tmx/Map.h>

using namespace tmx;

Layer::Layer()
: _map(nullptr)
, _visible(true)
, _opacity(1)
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

void Layer::setName(const QString& name)
{
	_name = name;
}

const QString& Layer::name() const
{
	return _name;
}

void Layer::setSize(const QSize& size)
{
	_size = size;
}

const QSize& Layer::size() const
{
	return _size;
}

void Layer::setWidth(int width)
{
	_size.setWidth(width);
}

int Layer::width() const
{
	return _size.width();
}

void Layer::setHeight(int height)
{
	_size.setHeight(height);
}

int Layer::height() const
{
	return _size.height();
}

void Layer::setOpacity(float opacity)
{
	_opacity = opacity;
}

float Layer::opacity() const
{
	return _opacity;
}

void Layer::setVisible(bool visible)
{
	_visible = visible;
}

bool Layer::isVisible() const
{
	return _visible;
}

