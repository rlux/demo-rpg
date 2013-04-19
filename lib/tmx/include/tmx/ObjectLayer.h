#pragma once

#include <tmx/Layer.h>
#include <tmx/Object.h>

#include <QColor>
#include <QList>

namespace tmx {

class ObjectLayer : public Layer
{
public:
	~ObjectLayer();

	virtual bool isObjectLayer() const;

	void setColor(const QColor& color);
	const QColor& color() const;

	void addObject(Object* object);
	const QList<Object*> objects() const;

	QString toString() const;
protected:
	QColor _color;
	QList<Object*> _objects;
};

} // namespace tmx
