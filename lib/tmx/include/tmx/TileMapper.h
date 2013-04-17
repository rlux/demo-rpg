#pragma once

#include <tmx/Tileset.h>
#include <tmx/Tile.h>

#include <QList>
#include <QHash>

namespace tmx {

class TileMapper
{
public:
	~TileMapper();

	void addTileset(Tileset* tileset);
	QList<Tileset*> tilesets() const;

	Tile* tile(unsigned gid) const;
protected:
	QList<Tileset*> _tilesets;
	mutable QHash<unsigned, Tile*> _tiles;
};

} // namespace tmx
