#include <tmx/ObjectLayer.h>

using namespace tmx;

ObjectLayer::~ObjectLayer()
{
	qDeleteAll(_objects);
}

bool ObjectLayer::isObjectLayer() const
{
	return true;
}

void ObjectLayer::setColor(const QColor& color)
{
	_color = color;
}

const QColor& ObjectLayer::color() const
{
	return _color;
}

void ObjectLayer::addObject(Object* object)
{
	_objects << object;
}

const QList<Object*> ObjectLayer::objects() const
{
	return _objects;
}

Object* ObjectLayer::objectNamed(const QString& name) const
{
	for (Object* object: _objects) {
		if (object->name()==name) return object;
	}
	return nullptr;
}

QString ObjectLayer::toString() const
{
	return QString("ObjectLayer");
}
