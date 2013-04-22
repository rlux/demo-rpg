#pragma once

#include <QPixmap>
#include <QSize>
#include <QRectF>
#include <QPainter>

class Animation
{
public:
	enum Direction {
		Left,
		Right,
		Up,
		Down
	};

	Animation();

	void setImage(const QString& filename);

	void setSize(const QSize& size);
	void setDuration(double duration);

	void render(QPainter& painter, const QRectF& area);

	QRect rect() const;
protected:
	Direction _direction;
	double _duration;
	double _current;
	QSize _size;
	QPixmap _pixmap;
	bool _running;
};
