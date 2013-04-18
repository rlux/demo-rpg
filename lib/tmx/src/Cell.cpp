#include <tmx/Cell.h>

using namespace tmx;

const unsigned Cell::FlippedHorizontallyFlag = 0x80000000;
const unsigned Cell::FlippedVerticallyFlag = 0x40000000;
const unsigned Cell::FlippedDiagonallyFlag = 0x20000000;
const unsigned Cell::AllFlippedFlags = Cell::FlippedHorizontallyFlag | Cell::FlippedVerticallyFlag | Cell::FlippedDiagonallyFlag;


Cell Cell::fromRawData(unsigned rawData, const TileMapper& tileMapper)
{
	bool flippedHorizontally = rawData & FlippedHorizontallyFlag;
	bool flippedVerticallyy = rawData & FlippedVerticallyFlag;
	bool flippedDiagonallyy = rawData & FlippedDiagonallyFlag;

	unsigned gid = rawData & ~AllFlippedFlags;

	Cell cell(tileMapper.tile(gid));

	return cell;
}


Cell::Cell()
: _tile(nullptr)
{
}

Cell::Cell(Tile* tile)
: _tile(tile)
{
}

Tile* Cell::tile() const
{
	return _tile;
}

void Cell::setTile(Tile* tile)
{
	_tile = tile;
}
