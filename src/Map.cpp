#include <Map.h>

#include <tmx/Loader.h>

#include <QDebug>

Map::Map(const QString& filename)
{
	_map = tmx::Loader::loadMap(filename);
}

Map::~Map()
{
	qDeleteAll(_objects);
	qDeleteAll(_triggers);
}

tmx::Map* Map::internalMap()
{
	return _map;
}

void Map::initialize(const NPCFactory& npcFactory)
{
	if (tmx::Layer* layer = _map->layerNamed("objects"))
	{
		if (tmx::ObjectLayer* objectLayer = layer->asObjectLayer())
		{
			for (tmx::Object* object: objectLayer->objects())
			{
				if (object->type()=="npc") {
					QPointF pos = object->position();
					if (object->shape()==tmx::Object::TileShape) pos.setY(pos.y()-_map->tileSize().height());
					NPC* npc = npcFactory.createNpc(object->name(), pos);
					_objects << npc;
				}
			}
		}
	}

	if (tmx::Layer* layer = _map->layerNamed("events"))
	{
		if (tmx::ObjectLayer* eventLayer = layer->asObjectLayer())
		{
			for (tmx::Object* object: eventLayer->objects())
			{
				EventTrigger* trigger = new EventTrigger();
				trigger->setPosition(object->position());
				trigger->setSize(object->size());
				trigger->setName(object->name());
				_triggers << trigger;
			}
		}
	}
}

const QList<AnimatedObject*>& Map::objects() const
{
	return _objects;
}

QSet<AnimatedObject*> Map::objectsIn(const QRectF& rect) const
{
	QSet<AnimatedObject*> objects;

	for (AnimatedObject* object: _objects)
	{
		if (object->marginedRect().intersects(rect))
		{
			objects << object;
		}
	}

	return objects;
}

const QList<EventTrigger*>& Map::triggers() const
{
	return _triggers;
}

QSet<EventTrigger*> Map::triggersIn(const QRectF& rect) const
{
	QSet<EventTrigger*> triggers;

	for (EventTrigger* trigger: _triggers)
	{
		if (trigger->rect().intersects(rect))
		{
			triggers << trigger;
		}
	}

	return triggers;
}
