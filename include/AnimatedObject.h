#pragma once

#include <QPointF>
#include <QSize>
#include <QRectF>
#include <QMargins>

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

	virtual bool isPlayer() const;
	virtual bool isNPC() const;

	const QPointF& position() const;
	void setPosition(const QPointF& position);

	QRectF rect() const;
	QRectF marginedRect() const;
	const QMargins& margins() const;
	void setMargins(const QMargins& margins);

	const QSize& size() const;
	void setSize(const QSize& size);
	double velocity() const;
	void setVelocity(double velocity);

	void setDirection(Direction direction);
	Direction direction() const;

	virtual void hitObstacle();

	Animation* animation();
protected:
	QPointF _position;
	double _velocity;
	Direction _direction;
	QSize _size;
	QMargins _margins;
	Animation _animation;
};
