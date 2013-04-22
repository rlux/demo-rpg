#include <tmx/TileLayer.h>
#include <tmx/TileMapper.h>
#include <tmx/Map.h>

#include <qmath.h>

using namespace tmx;

TileLayer::TileLayer()
{
}

bool TileLayer::isTileLayer() const
{
	return true;
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

QRect TileLayer::tileArea(const QRectF& pixelRect)
{
	const QSize& tileSize = _map->tileSize();

	int left = pixelRect.left()/tileSize.width();
	int top = pixelRect.top()/tileSize.height();
	int right = qCeil((float)pixelRect.right()/tileSize.width());
	int bottom = qCeil((float)pixelRect.bottom()/tileSize.height());

	left = qBound(0, left, width());
	right = qBound(0, right, width());
	top = qBound(0, top, height());
	bottom = qBound(0, bottom, height());

	return QRect(QPoint(left, top), QSize(right-left, bottom-top));
}

QString TileLayer::toString() const
{
	return QString("TileLayer(%1 %2x%3)").arg(_name).arg(_size.width()).arg(_size.height());
}
