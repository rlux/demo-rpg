#include <tmx/TileLayer.h>
#include <tmx/TileMapper.h>
#include <tmx/Map.h>

using namespace tmx;

TileLayer::TileLayer()
{
}

bool TileLayer::isTileLayer() const
{
	return true;
}

void TileLayer::setPosition(const QPoint& position)
{
	_position = position;
}

void TileLayer::setX(int x)
{
	_position.setX(x);
}

void TileLayer::setY(int y)
{
	_position.setY(y);
}

Cell& TileLayer::cellAt(int x, int y)
{
	return _cells[_size.width()*y+x];
}

Cell& TileLayer::cellAt(const QPoint& position)
{
	return cellAt(position.x(), position.y());
}

void TileLayer::setCellData(Data* data)
{
	_cells.resize(_size.width()*_size.height());

	const TileMapper& mapper = map()->tileMapper();
	for (int i=0; i<_cells.size(); ++i)
	{
		unsigned rawData = data->at<unsigned>(i);

		_cells[i] = Cell::fromRawData(rawData, mapper);
	}
}

QString TileLayer::toString() const
{
	return QString("TileLayer(%1 %2x%3)").arg(_name).arg(_size.width()).arg(_size.height());
}
