#pragma once

#include <NPC.h>
#include <NPCFactory.h>
#include <EventTrigger.h>

#include <QList>
#include <tmx/Map.h>

class Map
{
public:
	Map(const QString& filename);
	~Map();

	tmx::Map* internalMap();

	void initialize(const NPCFactory& npcFactory);

	const QList<AnimatedObject*>& objects() const;
	const QList<EventTrigger*>& triggers() const;

	QList<AnimatedObject*> objectsIn(const QRectF& rect) const;
protected:
	tmx::Map* _map;
	QList<AnimatedObject*> _objects;
	QList<EventTrigger*> _triggers;
};
