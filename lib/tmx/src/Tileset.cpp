#include <tmx/Tileset.h>

using namespace tmx;

Tileset::Tileset()
: _spacing(0)
, _margin(0)
{
}

Tileset::~Tileset()
{
	qDeleteAll(_tiles);
}

unsigned Tileset::firstGid() const
{
	return _firstGid;
}

const QString& Tileset::name() const
{
	return _name;
}

const QString& Tileset::source() const
{
	return _source;
}

int Tileset::spacing() const
{
	return _spacing;
}

int Tileset::margin() const
{
	return _margin;
}

const QSize& Tileset::tileSize() const
{
	return _tileSize;
}

void Tileset::setFirstGid(unsigned gid)
{
	_firstGid = gid;
}

void Tileset::setSource(const QString& source)
{
	_source = source;
}

void Tileset::setName(const QString& name)
{
	_name = name;
}

void Tileset::setSpacing(int spacing)
{
	_spacing = spacing;
}

void Tileset::setMargin(int margin)
{
	_margin = margin;
}

void Tileset::setTileSize(const QSize& size)
{
	_tileSize = size;
}

void Tileset::setTileWidth(int width)
{
	_tileSize.setWidth(width);
}

void Tileset::setTileHeight(int height)
{
	_tileSize.setHeight(height);
}

const QPoint& Tileset::tileOffset() const
{
	return _tileOffset;
}

void Tileset::setTileOffset(const QPoint& offset)
{
	_tileOffset = offset;
}

Image* Tileset::image()
{
	return &_image;
}

Tile* Tileset::atGid(unsigned gid)
{
	return at(gid-_firstGid);
}

Tile* Tileset::at(unsigned id)
{
	if (!_tiles.contains(id)) {
		_tiles.insert(id, new Tile(id, this));
	}
	return _tiles[id];
}

QString Tileset::toString() const
{
	return QString("Tileset(%1 %2 %3 %4 %5 %6x%7 %8)").arg(_name).arg(_firstGid).arg(_spacing).arg(_margin).arg(_source).arg(_tileOffset.x()).arg(_tileOffset.y()).arg(_image.source());
}
