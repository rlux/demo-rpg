#include <tmx/TileLayer.h>
#include <tmx/TileMapper.h>
#include <tmx/Map.h>

using namespace tmx;

TileLayer::TileLayer()
: _visible(true)
, _opacity(1)
{
}

bool TileLayer::isTileLayer() const
{
	return true;
}

void TileLayer::setName(const QString& name)
{
	_name = name;
}

void TileLayer::setSize(const QSize& size)
{
	_size = size;
}

void TileLayer::setWidth(int width)
{
	_size.setWidth(width);
}

void TileLayer::setHeight(int height)
{
	_size.setHeight(height);
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

void TileLayer::setOpacity(float opacity)
{
	_opacity = opacity;
}

void TileLayer::setVisible(bool visible)
{
	_visible = visible;
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
		unsigned rawData = ((unsigned*)data->bytes().data())[i];

		_cells[i] = Cell::fromRawData(rawData, mapper);
	}
}

QString TileLayer::toString() const
{
	return QString("TileLayer(%1 %2x%3)").arg(_name).arg(_size.width()).arg(_size.height());
}
