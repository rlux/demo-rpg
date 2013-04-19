#pragma once

#include <tmx/Layer.h>
#include <tmx/Data.h>
#include <tmx/Cell.h>

#include <QString>
#include <QSize>
#include <QPoint>
#include <QVector>

namespace tmx {

class TileLayer : public Layer
{
public:
	TileLayer();

	virtual bool isTileLayer() const;

	void setPosition(const QPoint& position);
	void setX(int x);
	void setY(int y);
	void setOpacity(float opacity);
	void setVisible(bool visible);

	Cell& cellAt(int x, int y);
	Cell& cellAt(const QPoint& position);

	void setCellData(Data* data);

	QString toString() const;
protected:
	QPoint _position;
	float _opacity;
	bool _visible;
	QVector<Cell> _cells;
};

} // namespace tmx
