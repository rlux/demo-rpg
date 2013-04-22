#pragma once

#include <Game.h>

class Engine
{
public:
	Engine(Game* game);

	void update(double delta);
protected:
	Game* _game;

	void moveObjects(double delta);

	tmx::TileLayer* walkableLayer();
	bool canMoveTo(AnimatedObject* object, const QPointF& pos);
	bool inMap(const QRectF& rect);
};
