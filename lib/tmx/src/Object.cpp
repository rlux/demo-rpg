#include <tmx/Object.h>

using namespace tmx;

Object::Object()
: _visible(true)
, _gid(0)
{
}


void Object::setName(const QString& name)
{
	_name = name;
}

const QString& Object::name() const
{
	return _name;
}

void Object::setType(const QString& type)
{
	_type = type;
}

const QString& Object::type() const
{
	return _type;
}

void Object::setSize(const QSize& size)
{
	_size = size;
}

const QSize& Object::size() const
{
	return _size;
}

void Object::setWidth(int width)
{
	_size.setWidth(width);
}

int Object::width() const
{
	return _size.width();
}

void Object::setHeight(int height)
{
	_size.setHeight(height);
}

int Object::height() const
{
	return _size.height();
}

void Object::setPosition(const QPoint& position)
{
	_position = position;
}

const QPoint& Object::position() const
{
	return _position;
}

void Object::setX(int x)
{
	_position.setX(x);
}

void Object::setY(int y)
{
	_position.setY(y);
}

void Object::setVisible(bool visible)
{
	_visible = visible;
}

bool Object::isVisible() const
{
	return _visible;
}

void Object::setGid(unsigned gid)
{
	_gid = gid;
}

unsigned Object::gid() const
{
	return _gid;
}
