#pragma once

#include <AnimatedObject.h>
#include <EventTrigger.h>

#include <tmx/TileLayer.h>

#include <QList>
#include <QSet>

class Game;

class Engine : public QObject
{
	Q_OBJECT
public:
	Engine(Game* game);

	void update(double delta);
protected slots:
	void mapChanged();
protected:
	Game* _game;

	void moveObjects(double delta);
	void moveObject(AnimatedObject* object, double delta);

	void checkTriggers(AnimatedObject* object, QSet<EventTrigger*>& currentTriggers);

	tmx::TileLayer* walkableLayer();
	bool canBeAt(AnimatedObject* object, const QPointF& pos);
	bool inMap(const QRectF& rect);

	QList<QPointF> wayPoints(AnimatedObject* object, double distance);
	QList<QRectF> obstaclesIn(const QRectF& area, AnimatedObject* object);
};
