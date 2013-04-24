#pragma once

#include <AnimatedObject.h>

#include <QString>

class MapEvent
{
public:
	MapEvent(AnimatedObject* trigger);
	virtual ~MapEvent();

	const AnimatedObject* trigger() const;
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
