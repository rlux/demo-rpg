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

void EventTrigger::ignore(AnimatedObject* object)
{
	_ignored << object;
}

void EventTrigger::trigger(AnimatedObject* object)
{
//	qDebug() << "trigger"<<_type <<  _name;

	if (_ignored.contains(object)) return;

	if (_type=="changemap")
	{
		if (!object->isPlayer()) return;
		trigger(new MapChangeEvent(object, _properties["map"], _properties["target"]));
	}
	else if (_type=="teleport")
	{
		trigger(new TeleportEvent(object, _properties["target"]));
	}

	_ignored << object;
}

void EventTrigger::enter(AnimatedObject* object)
{
//	qDebug() << "enter"<<_type <<  _name;
}

void EventTrigger::move(AnimatedObject* object)
{
//	qDebug() << "move"<<_type <<  _name;

	QRectF objectRect = object->marginedRect();
	double objectArea = objectRect.width()*objectRect.height();

	QRectF triggerRect = rect();
	double triggerArea = triggerRect.width()*triggerRect.height();
	QRectF intersected = triggerRect.intersected(objectRect);
	double intersectedArea = intersected.width()*intersected.height();

	double ratio = intersectedArea/qMin(objectArea, triggerArea);

	if (ratio>0.5) trigger(object);
}

void EventTrigger::exit(AnimatedObject* object)
{
//	qDebug() << "exit" << _type <<  _name;

	_ignored.remove(object);
}
