#include <EventTrigger.h>

#include <QDebug>

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

void EventTrigger::setName(const QString& name)
{
	_name = name;
}

const QString& EventTrigger::name() const
{
	return _name;
}

QRectF EventTrigger::rect() const
{
	return QRectF(_position, _size);
}

void EventTrigger::enter(AnimatedObject* object)
{
	qDebug() << "enter" << object;
	object->setPosition(QPointF(100,200));
}

void EventTrigger::exit(AnimatedObject* object)
{
	qDebug() << "exit" << object;
}
