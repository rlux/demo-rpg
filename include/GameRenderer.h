#pragma once

#include <tmx/Renderer.h>

class Game;
class Player;

class GameRenderer : public tmx::Renderer
{
public:
	GameRenderer(Game* game);

	void renderGame(QPainter& painter);
protected:
	Game* _game;

	virtual void renderLayers(QPainter& painter, tmx::Map* map);
	void renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name);

	void renderPlayer(QPainter& painter, Player* player);
};
