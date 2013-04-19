#include <tmx/Tile.h>
#include <tmx/Tileset.h>

using namespace tmx;

Tile::Tile()
: _index(0)
, _tileset(nullptr)
{
}

Tile::Tile(unsigned index, Tileset* tileset)
: _index(index)
, _tileset(tileset)
{
	updateRect();
}

Tileset* Tile::tileset() const
{
	return _tileset;
}

void Tile::setTileset(Tileset* tileset)
{
	_tileset = tileset;
	updateRect();
}

unsigned Tile::index() const
{
	return _index;
}

void Tile::setIndex(unsigned index)
{
	_index = index;
	updateRect();
}

QRect Tile::rect() const
{
	return _rect;
}

void Tile::setName(const QString& name)
{
	_name = name;
}

const QString& Tile::name() const
{
	return _name;
}

void Tile::updateRect()
{
	if (!_tileset)
	{
		_rect = QRect();
		return;
	}

	const QSize& size = _tileset->tileSize();
	int w = _tileset->image()->width()/size.width();
	unsigned x = _index%w;
	unsigned y = _index/w;

	_rect = QRect(QPoint(x*size.width(), y*size.height()), size);
}
