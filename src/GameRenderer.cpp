#include <GameRenderer.h>
#include <Game.h>

#include <QDebug>

void GameRenderer::renderGame(QPainter& painter, Game* game)
{
	renderMap(painter, game->map());
}

void GameRenderer::renderLayers(QPainter& painter, tmx::Map* map)
{
	renderLayerNamed(painter, map, "ground");
	renderLayerNamed(painter, map, "decoration");
	renderLayerNamed(painter, map, "spawn");
}

void GameRenderer::renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name)
{
	tmx::Layer* layer = map->layerNamed(name);
	if (layer) renderLayer(painter, layer);
	else qDebug() << name;
}
