#pragma once

#include <Game.h>

#include <QList>
#include <QHash>
#include <QSet>

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
	QHash<AnimatedObject*, QSet<EventTrigger*>> _currentTriggers;

	void moveObjects(double delta);
	void moveObject(AnimatedObject* object, double delta);

	void checkTriggers(AnimatedObject* object);

	tmx::TileLayer* walkableLayer();
	bool canBeAt(AnimatedObject* object, const QPointF& pos);
	bool inMap(const QRectF& rect);

	QList<QPointF> wayPoints(AnimatedObject* object, double distance);
	QList<QRectF> obstaclesIn(const QRectF& area, AnimatedObject* object);
};
