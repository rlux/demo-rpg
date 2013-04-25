#pragma once

#include <NPC.h>
#include <NPCFactory.h>
#include <EventTrigger.h>

#include <QList>
#include <QSet>
#include <tmx/Map.h>

class Map : public QObject
{
	Q_OBJECT
public:
	Map(const QString& filename);
	~Map();

	bool isValid() const;
	tmx::Map* internalMap();

	void initialize(const NPCFactory& npcFactory);

	const QList<AnimatedObject*>& objects() const;
	const QList<EventTrigger*>& triggers() const;

	QSet<AnimatedObject*> objectsIn(const QRectF& rect) const;
	QSet<EventTrigger*> triggersIn(const QRectF& rect) const;

	QRectF target(const QString& name);

	void moveObjectToTarget(AnimatedObject* object, const QString& name);
signals:
	void eventTriggered(MapEvent* event);
protected:
	tmx::Map* _map;
	QList<AnimatedObject*> _objects;
	QList<EventTrigger*> _triggers;
};
