#pragma once

#include <QPointF>
#include <QSize>
#include <QRectF>

class EventTrigger
{
public:
	const QPointF& position() const;
	void setPosition(const QPointF& position);

	QRectF rect() const;

	const QSize& size() const;
	void setSize(const QSize& size);
protected:
	QPointF _position;
	QSize _size;
};
