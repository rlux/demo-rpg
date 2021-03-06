#pragma once

#include <AnimatedObject.h>
#include <MapEvent.h>

#include <QPointF>
#include <QSize>
#include <QRectF>
#include <QHash>

#include <tmx/Object.h>

class EventTrigger : public QObject
{
	Q_OBJECT
public:
	EventTrigger(tmx::Object* object);

	const QPointF& position() const;
	void setPosition(const QPointF& position);

	void setName(const QString& name);
	const QString& name() const;

	QRectF rect() const;

	const QSize& size() const;
	void setSize(const QSize& size);

	bool intersects(const QRectF& rect);

	void enter(AnimatedObject* object);
	void exit(AnimatedObject* object);
signals:
	void triggered(MapEvent* event);
protected:
	QPointF _position;
	QSize _size;
	QString _name;
	QString _type;
	QHash<QString, QString> _properties;

	void trigger(AnimatedObject* object);
	void trigger(MapEvent* event);
};
