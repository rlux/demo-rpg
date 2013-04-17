#pragma once

#include <tmx/Base.h>
#include <tmx/Data.h>

#include <QString>
#include <QSize>
#include <QPoint>

namespace tmx {

class TileLayer : public Base
{
public:
	TileLayer();

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

	QString toString() const;
protected:
	QString _name;
	QPoint _position;
	QSize _size;
	float _opacity;
	bool _visible;
	Data _data;

	int at(int x, int y) const;
};

} // namespace tmx
