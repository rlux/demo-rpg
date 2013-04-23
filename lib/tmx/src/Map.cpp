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
	qDeleteAll(_layers);
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

const QSize& Map::size() const
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

const QSize& Map::tileSize() const
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

QSize Map::pixelSize() const
{
	return QSize(_size.width()*_tileSize.width(), _size.height()*_tileSize.height());
}

const QColor& Map::backgroundColor() const
{
	return _backgroundColor;
}

void Map::setBackgroundColor(const QColor& color)
{
	_backgroundColor = color;
}

void Map::setFilename(const QString& filename)
{
	_filename = filename;
}

const QString& Map::filename() const
{
	return _filename;
}

void Map::addTileset(Tileset* tileset)
{
	_tileMapper.addTileset(tileset);
}

const QList<Tileset*>& Map::tilesets() const
{
	return _tileMapper.tilesets();
}

const TileMapper& Map::tileMapper() const
{
	return _tileMapper;
}

void Map::addLayer(Layer* layer)
{
	layer->setMap(this);
	_layers << layer;
}

const QList<Layer*>& Map::layers() const
{
	return _layers;
}

QList<TileLayer*> Map::tileLayers() const
{
	QList<TileLayer*> layers;

	for (Layer* layer: _layers) {
		if (layer->isTileLayer()) layers << layer->asTileLayer();
	}

	return layers;
}

QList<ImageLayer*> Map::imageLayers() const
{
	QList<ImageLayer*> layers;

	for (Layer* layer: _layers) {
		if (layer->isImageLayer()) layers << layer->asImageLayer();
	}

	return layers;
}

QList<ObjectLayer*> Map::objectLayers() const
{
	QList<ObjectLayer*> layers;

	for (Layer* layer: _layers) {
		if (layer->isObjectLayer()) layers << layer->asObjectLayer();
	}

	return layers;
}

Layer* Map::layerNamed(const QString& name) const
{
	for (Layer* layer: _layers) {
		if (layer->name()==name) return layer;
	}

	return nullptr;
}

QString Map::toString() const
{
	QString sets;
	for (Tileset* tileset: _tileMapper.tilesets()) {
		sets += tileset->toString() + "\n";
	}
	QString layers;
	for (Layer* layer: _layers) {
		layers += layer->toString() + "\n";
	}

	return QString("Map(%1 %2x%3 %4x%5\n%6 %7)").arg((unsigned)_orientation).arg(_size.width()).arg(_size.height()).arg(_tileSize.width()).arg(_tileSize.height()).arg(sets).arg(layers);
}
