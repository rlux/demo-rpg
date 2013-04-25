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

void EventTrigger::trigger(AnimatedObject* object)
{
	qDebug() << "trigger"<<_type <<  _name;

	if (_type=="changemap")
	{
		if (!object->isPlayer()) return;
		trigger(new MapChangeEvent(object, _properties["map"], _properties["target"]));
	}
	else if (_type=="teleport")
	{
		trigger(new TeleportEvent(object, _properties["target"]));
	}
}

void EventTrigger::enter(AnimatedObject* object)
{
//	qDebug() << "enter"<<_type <<  _name;
	trigger(object);
}

bool EventTrigger::intersects(const QRectF& rect)
{
	QRectF triggerRect = this->rect();

	if (triggerRect.contains(rect)) return true;

	QRectF intersected = triggerRect.intersected(rect);

	double p = qMax(intersected.width()/triggerRect.width(), intersected.height()/triggerRect.height());

	return p>0.5;
}

void EventTrigger::exit(AnimatedObject* object)
{
//	qDebug() << "exit" << _type <<  _name;
}
