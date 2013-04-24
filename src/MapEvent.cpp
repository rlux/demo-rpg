#include <MapEvent.h>


MapEvent::MapEvent(AnimatedObject* trigger)
: _trigger(trigger)
{
}

MapEvent::~MapEvent()
{

}

const AnimatedObject* MapEvent::trigger() const
{
	return _trigger;
}

TeleportEvent::TeleportEvent(AnimatedObject* trigger, const QString& target)
: MapEvent(trigger)
, _target(target)
{
}

const QString& TeleportEvent::target() const
{
	return _target;
}

MapChangeEvent::MapChangeEvent(AnimatedObject* trigger, const QString& mapName, const QString& target)
: MapEvent(trigger)
, _mapName(mapName)
, _target(target)
{
}

const QString& MapChangeEvent::mapName() const
{
	return _mapName;
}

const QString& MapChangeEvent::target() const
{
	return _target;
}
