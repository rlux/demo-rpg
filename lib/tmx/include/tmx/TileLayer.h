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

	void setName(const QString& name);
	void setSize(const QSize& size);
	void setWidth(int width);
	void setHeight(int height);
	void setPosition(const QPoint& position);
	void setX(int x);
	void setY(int y);
	void setOpacity(float opacity);
	void setVisible(bool visible);

	Data& data();
	void createCells();

	QString toString() const;
protected:
	QString _name;
	QPoint _position;
	QSize _size;
	float _opacity;
	bool _visible;
	Data _data;
	QVector<Cell> _cells;

	int at(int x, int y) const;
};

} // namespace tmx
