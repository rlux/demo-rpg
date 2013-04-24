#pragma once

#include <Game.h>

#include <QList>

class Engine
{
public:
	Engine(Game* game);

	void update(double delta);
protected:
	Game* _game;

	void moveObjects(double delta);
	void moveObject(AnimatedObject* object, double delta);

	QList<double> splitStep(double start, double d, double step);

	tmx::TileLayer* walkableLayer();
	bool canBeAt(AnimatedObject* object, const QPointF& pos);
	bool inMap(const QRectF& rect);

	QList<QPointF> wayPoints(AnimatedObject* object, double distance);
	QList<QRectF> obstaclesIn(const QRectF& area, AnimatedObject* object);
	QList<AnimatedObject*> objectsIn(const QRectF& area);
};
