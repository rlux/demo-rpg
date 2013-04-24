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

bool Map::isValid() const
{
	return _map!=nullptr;
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
				EventTrigger* trigger = new EventTrigger(object);
				connect(trigger, SIGNAL(triggered(MapEvent*)), this, SIGNAL(eventTriggered(MapEvent*)));
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

QPointF Map::target(const QString& name)
{
	QPointF pos;
	if (tmx::Layer* layer = _map->layerNamed("spawn"))
	{
		if (tmx::ObjectLayer* oLayer = layer->asObjectLayer())
		{
			if (tmx::Object* o = oLayer->objectNamed(name))
			{
				pos = o->position();
			}
		}
	}
	if (tmx::Layer* layer = _map->layerNamed("events"))
	{
		if (tmx::ObjectLayer* oLayer = layer->asObjectLayer())
		{
			if (tmx::Object* o = oLayer->objectNamed(name))
			{
				pos = o->position();
			}
		}
	}
	return pos;
}
