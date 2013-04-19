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

QString ObjectLayer::toString() const
{
	return QString("ObjectLayer");
}
