#pragma once

#include <tmx/Renderer.h>

class Game;
class Map;
class AnimatedObject;
class EventTrigger;

class GameRenderer : public QObject, public tmx::Renderer
{
	Q_OBJECT
public:
	GameRenderer(Game* game);

	void renderGame(QPainter& painter);
protected slots:
	void mapChanged();
protected:
	Game* _game;

	void calculateOffset();

	virtual void renderLayers(QPainter& painter, tmx::Map* map);
	void renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name);
	void renderObjects(QPainter& painter);
	void renderObject(QPainter& painter, AnimatedObject* object);

	void renderEventTriggers(QPainter& painter);
	void renderEventTrigger(QPainter& painter, EventTrigger* trigger);
};
