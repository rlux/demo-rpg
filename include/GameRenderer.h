#pragma once

#include <tmx/Renderer.h>

class Game;
class AnimatedObject;

class GameRenderer : public tmx::Renderer
{
public:
	GameRenderer(Game* game);

	void renderGame(QPainter& painter);
protected:
	Game* _game;

	void calculateOffset();

	virtual void renderLayers(QPainter& painter, tmx::Map* map);
	void renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name);
	void renderObjects(QPainter& painter);
	void renderObject(QPainter& painter, AnimatedObject* object);
};
