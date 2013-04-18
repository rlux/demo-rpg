#pragma once

#include <tmx/Tile.h>
#include <tmx/TileMapper.h>

namespace tmx {

class Cell
{
public:
	Cell();
	Cell(Tile* tile);

	static Cell fromRawData(unsigned rawData, const TileMapper& tileMapper);

	Tile* tile() const;
	void setTile(Tile* tile);
protected:
	bool _flippedHorizontally;
	bool _flippedVertically;
	bool _flippedDiagonally;
	Tile* _tile;

	static const unsigned FlippedHorizontallyFlag;
	static const unsigned FlippedVerticallyFlag;
	static const unsigned FlippedDiagonallyFlag;
	static const unsigned AllFlippedFlags;
};

} // namespace tmx
