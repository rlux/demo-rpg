#include <tmx/Map.h>

using namespace tmx;

Map::Map()
: _orientation(Invalid)
{
}

Map::Map(Orientation orientation, const QSize& size, const QSize& tileSize)
: _orientation(orientation)
, _size(size)
, _tileSize(tileSize)
{
}

Map::~Map()
{
	qDeleteAll(_tilesets);
}

Map::Orientation Map::orientation() const
{
	return _orientation;
}

void Map::setOrientation(Orientation orientation)
{
	_orientation = orientation;
}

Map::Orientation Map::orientationFromString(const QString& name)
{
	if (name=="orthogonal") {
		return Orthogonal;
	} else if (name=="isometric") {
		return Isometric;
	} else if (name=="staggered") {
		return Staggered;
	} else {
		return Invalid;
	}
}

QSize Map::size() const
{
	return _size;
}

int Map::width() const
{
	return _size.width();
}

int Map::height() const
{
	return _size.height();
}

void Map::setSize(const QSize& size)
{
	_size = size;
}

void Map::setWidth(int width)
{
	_size.setWidth(width);
}

void Map::setHeight(int height)
{
	_size.setHeight(height);
}

QSize Map::tileSize() const
{
	return _tileSize;
}

int Map::tileWidth() const
{
	return _tileSize.width();
}

int Map::tileHeight() const
{
	return _tileSize.height();
}

void Map::setTileSize(const QSize& size)
{
	_tileSize = size;
}

void Map::setTileWidth(int width)
{
	_tileSize.setWidth(width);
}

void Map::setTileHeight(int height)
{
	_tileSize.setHeight(height);
}

void Map::addTileset(Tileset* tileset)
{
	_tilesets << tileset;
}

void Map::addLayer(Layer* layer)
{
	layer->setMap(this);
	_layers << layer;
}

QString Map::toString() const
{
	QString sets;
	for (Tileset* tileset: _tilesets) {
		sets += tileset->toString() + "\n";
	}
	QString layers;
	for (Layer* layer: _layers) {
		layers += layer->toString() + "\n";
	}

	return QString("Map(%1 %2x%3 %4x%5\n%6 %7)").arg((unsigned)_orientation).arg(_size.width()).arg(_size.height()).arg(_tileSize.width()).arg(_tileSize.height()).arg(sets).arg(layers);
}
