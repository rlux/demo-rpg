#include <GameRenderer.h>
#include <Game.h>

#include <QDebug>

GameRenderer::GameRenderer(Game* game)
: _game(game)
{
}

void GameRenderer::renderGame(QPainter& painter)
{
	renderMap(painter, _game->map());
}

void GameRenderer::renderLayers(QPainter& painter, tmx::Map* map)
{
	renderLayerNamed(painter, map, "ground");
	renderLayerNamed(painter, map, "decoration");
	renderPlayer(painter, _game->player());
}

void GameRenderer::renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name)
{
	tmx::Layer* layer = map->layerNamed(name);
	if (layer) renderLayer(painter, layer);
	else qDebug() << name;
}

void GameRenderer::renderPlayer(QPainter& painter, Player* player)
{
	QPoint pos = player->position();
	painter.fillRect(QRect(pos, QSize(32,32)), Qt::blue);
}
