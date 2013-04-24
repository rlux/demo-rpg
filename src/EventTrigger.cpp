#include <EventTrigger.h>

#include <QDebug>

EventTrigger::EventTrigger(tmx::Object* object)
{
	setPosition(object->position());
	setSize(object->size());
	setName(object->name());
	_type = object->type();
	_properties = object->properties();
}

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

void EventTrigger::trigger(MapEvent* event)
{
	emit(triggered(event));
}

void EventTrigger::enter(AnimatedObject* object)
{
	if (!object->isPlayer()) return;

	if (_type=="changemap")
	{
		trigger(new MapChangeEvent(object, _properties["map"], _properties["target"]));
	}
	else if (_type=="teleport")
	{
		trigger(new TeleportEvent(object, _properties["target"]));
	}
}

void EventTrigger::exit(AnimatedObject* object)
{
}
