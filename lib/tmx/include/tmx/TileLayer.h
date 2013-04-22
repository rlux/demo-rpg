#pragma once

#include <tmx/Layer.h>
#include <tmx/Data.h>
#include <tmx/Cell.h>

#include <QString>
#include <QSize>
#include <QPoint>
#include <QVector>
#include <QRectF>

namespace tmx {

class TileLayer : public Layer
{
public:
	TileLayer();

	virtual bool isTileLayer() const;

	Cell& cellAt(int x, int y);
	Cell& cellAt(const QPoint& position);

	void setCellData(Data* data);

	QRect tileArea(const QRectF& pixelRect);

	QString toString() const;
protected:
	QVector<Cell> _cells;
};

} // namespace tmx
