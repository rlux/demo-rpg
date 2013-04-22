#include <AnimatedObject.h>

AnimatedObject::AnimatedObject()
: _velocity(1.0)
, _direction(None)
, _margin(0)
{
	_size = QSize(32,32);
}

const QPointF& AnimatedObject::position() const
{
	return _position;
}

void AnimatedObject::setPosition(const QPointF& position)
{
	_position = position;
}

const QSize& AnimatedObject::size() const
{
	return _size;
}

QRectF AnimatedObject::rect() const
{
	return QRectF(_position, _size);
}

QRectF AnimatedObject::marginedRect() const
{
	return rect().adjusted(_margin, _margin, -_margin, -_margin);
}

int AnimatedObject::margin() const
{
	return _margin;
}

double AnimatedObject::velocity() const
{
	return _velocity;
}

void AnimatedObject::setVelocity(double velocity)
{
	_velocity = velocity;
}

void AnimatedObject::setDirection(Direction direction)
{
	_direction = direction;
}

AnimatedObject::Direction AnimatedObject::direction() const
{
	return _direction;
}

Animation* AnimatedObject::animation()
{
	return &_animation;
}
