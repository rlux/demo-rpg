#pragma once

#include <QRect>

namespace tmx {

class Tileset;

class Tile
{
public:
	Tile();
	Tile(unsigned index, Tileset* tileset);

	QRect rect() const;
protected:
	Tileset* _tileset;
	unsigned _index;
};

} // namespace tmx
