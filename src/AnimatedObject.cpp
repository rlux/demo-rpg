#include <AnimatedObject.h>

AnimatedObject::AnimatedObject()
: _velocity(1.0)
, _direction(None)
{
	_size = QSize(32,32);
}

bool AnimatedObject::isPlayer() const
{
	return false;
}

bool AnimatedObject::isNPC() const
{
	return false;
}

const QPointF& AnimatedObject::position() const
{
	return _position;
}

void AnimatedObject::setPosition(const QPointF& position)
{
	_position = position;
}

void AnimatedObject::moveBy(const QPointF& d)
{
	_position += d;
}

void AnimatedObject::moveBy(double dx, double dy)
{
	moveBy(QPointF(dx, dy));
}

const QSize& AnimatedObject::size() const
{
	return _size;
}

void AnimatedObject::setSize(const QSize& size)
{
	_size = size;
}

QRectF AnimatedObject::rect() const
{
	return QRectF(_position, _size);
}

QRectF AnimatedObject::marginedRect() const
{
	return rect().adjusted(_margins.left(), _margins.top(), _margins.right(), _margins.bottom());
}

const QMargins&  AnimatedObject::margins() const
{
	return _margins;
}

void AnimatedObject::setMargins(const QMargins& margins)
{
	_margins = margins;
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

	switch (_direction)
	{
		case None:
			_animation.setRunning(false);
			break;
		case Left:
			_animation.setRunning(true);
			_animation.setDirection(Animation::Left);
			break;
		case Right:
			_animation.setRunning(true);
			_animation.setDirection(Animation::Right);
			break;
		case Up:
			_animation.setRunning(true);
			_animation.setDirection(Animation::Up);
			break;
		case Down:
			_animation.setRunning(true);
			_animation.setDirection(Animation::Down);
			break;
	}
}

AnimatedObject::Direction AnimatedObject::direction() const
{
	return _direction;
}

Animation* AnimatedObject::animation()
{
	return &_animation;
}

void AnimatedObject::hitObstacle()
{
}
