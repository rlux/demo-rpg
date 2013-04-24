#include <EventTrigger.h>

const QPointF& EventTrigger::position() const
{
	return _position;
}

void EventTrigger::setPosition(const QPointF& position)
{
	_position = position;
}

const QSize& EventTrigger::size() const
{
	return _size;
}

void EventTrigger::setSize(const QSize& size)
{
	_size = size;
}

QRectF EventTrigger::rect() const
{
	return QRectF(_position, _size);
}
