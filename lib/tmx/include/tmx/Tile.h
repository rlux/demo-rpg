#pragma once

#include <QRect>

namespace tmx {

class Tileset;

class Tile
{
public:
	Tile();
	Tile(unsigned index, Tileset* tileset);

	Tileset* tileset() const;
	void setTileset(Tileset* tileset);

	unsigned index() const;
	void setIndex(unsigned index);

	QRect rect() const;
protected:
	Tileset* _tileset;
	unsigned _index;
	QRect _rect;

	void updateRect();
};

} // namespace tmx
