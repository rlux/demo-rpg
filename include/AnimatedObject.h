#pragma once

#include <QPointF>
#include <QSize>
#include <QRectF>

#include <Animation.h>

class AnimatedObject
{
public:
	enum Direction {
		None,
		Left ,
		Right,
		Up,
		Down
	};

	AnimatedObject();

	const QPointF& position() const;
	void setPosition(const QPointF& position);

	QRectF rect() const;
	QRectF marginedRect() const;
	int margin() const;

	const QSize& size() const;
	double velocity() const;
	void setVelocity(double velocity);

	void setDirection(Direction direction);
	Direction direction() const;

	Animation* animation();
protected:
	QPointF _position;
	double _velocity;
	Direction _direction;
	QSize _size;
	int _margin;
	Animation _animation;
};
