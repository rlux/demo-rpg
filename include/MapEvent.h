#pragma once

#include <AnimatedObject.h>

#include <QString>

class MapEvent
{
public:
	MapEvent(AnimatedObject* trigger);
	virtual ~MapEvent();

	AnimatedObject* trigger();
protected:
	AnimatedObject* _trigger;
};

class MapChangeEvent : public MapEvent
{
public:
	MapChangeEvent(AnimatedObject* trigger, const QString& mapName, const QString& target);

	const QString& mapName() const;
	const QString& target() const;
protected:
	QString _mapName;
	QString _target;
};

class TeleportEvent : public MapEvent
{
public:
	TeleportEvent(AnimatedObject* trigger, const QString& target);

	const QString& target() const;
protected:
	QString _target;
};

