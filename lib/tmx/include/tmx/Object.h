#pragma once

#include <tmx/Base.h>
#include <tmx/Tile.h>

#include <QPoint>
#include <QSize>
#include <QString>
#include <QVector>

namespace tmx {

class Object : public Base
{
public:
	enum Shape {
		Rectangle,
		Ellipse,
		Polygon,
		Polyline,
		TileShape
	};

	Object();

	void setName(const QString& name);
	const QString& name() const;

	void setType(const QString& type);
	const QString& type() const;

	void setSize(const QSize& size);
	const QSize& size() const;
	void setWidth(int width);
	int width() const;
	void setHeight(int height);
	int height() const;

	void setPosition(const QPoint& position);
	const QPoint& position() const;
	void setX(int x);
	void setY(int y);

	QRect rect() const;

	void setVisible(bool visible);
	bool isVisible() const;

	void setTile(Tile* tile);
	Tile* tile() const;

	void setPoints(const QVector<QPoint>& points);
	const QVector<QPoint>& points();

	Shape shape() const;
	void setShape(Shape shape);
protected:
	QString _name;
	QString _type;
	QPoint _position;
	QSize _size;
	bool _visible;
	Tile* _tile;
	QVector<QPoint> _points;
	Shape _shape;
};

} // namespace tmx
