#pragma once

#include <tmx/Renderer.h>

class Game;

class GameRenderer : public tmx::Renderer
{
public:
	void renderGame(QPainter& painter, Game* game);
protected:
	virtual void renderLayers(QPainter& painter, tmx::Map* map);
	virtual void renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name);
};
