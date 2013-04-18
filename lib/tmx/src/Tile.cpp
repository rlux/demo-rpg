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
}

Tileset* Tile::tileset() const
{
	return _tileset;
}

QRect Tile::rect() const
{
	if (!_tileset) return QRect();

	const QSize& size = _tileset->tileSize();
	int w = _tileset->image().width()/size.width();
	unsigned x = _index%w;
	unsigned y = _index/w;

	return QRect(QPoint(x*size.width(), y*size.height()), size);
}
