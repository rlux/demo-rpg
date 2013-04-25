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
	enum DebugRenderFlags
	{
		NoDebugRender = 0x0,
		RenderEvents = 0x1,
		RenderWalkable = 0x2,
		RenderCollisionVolume = 0x4
	};

	GameRenderer(Game* game);

	void renderGame(QPainter& painter);

	void toggleRenderFlag(DebugRenderFlags flag);
protected slots:
	void mapChanged();
protected:
	Game* _game;
	unsigned _debugRenderFlags;

	void calculateOffset();

	virtual void renderLayers(QPainter& painter, tmx::Map* map);
	void renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name);
	void renderObjects(QPainter& painter);
	void renderObject(QPainter& painter, AnimatedObject* object);

	void renderEventTriggers(QPainter& painter);
	void renderEventTrigger(QPainter& painter, EventTrigger* trigger);
};
