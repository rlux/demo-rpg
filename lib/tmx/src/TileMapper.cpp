#include <tmx/TileMapper.h>

using namespace tmx;

TileMapper::~TileMapper()
{
	qDeleteAll(_tilesets);
	qDeleteAll(_tiles);
}

void TileMapper::addTileset(Tileset* tileset)
{
	_tilesets << tileset;
}

QList<Tileset*> TileMapper::tilesets() const
{
	return _tilesets;
}

Tile* TileMapper::tile(unsigned gid) const
{
	Tileset* t = nullptr;
	for (Tileset* tileset: _tilesets)
	{
		if (gid<tileset->firstGid()) break;
		t = tileset;
	}
	;
	return nullptr;
}
