#pragma once

#include <AnimatedObject.h>

#include <QPointF>
#include <QSize>
#include <QRectF>

class EventTrigger
{
public:
	const QPointF& position() const;
	void setPosition(const QPointF& position);

	void setName(const QString& name);
	const QString& name() const;

	QRectF rect() const;

	const QSize& size() const;
	void setSize(const QSize& size);

	virtual void enter(AnimatedObject* object);
	virtual void exit(AnimatedObject* object);
protected:
	QPointF _position;
	QSize _size;
	QString _name;
};
