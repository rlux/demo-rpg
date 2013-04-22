#include <GameRenderer.h>
#include <Game.h>

#include <QDebug>

GameRenderer::GameRenderer(Game* game)
: _game(game)
{
}

void GameRenderer::renderGame(QPainter& painter)
{
	QPoint pos = _game->player()->position().toPoint();
	QPoint size = QPoint(_viewport.width(), _viewport.height());
	setOffset(_viewport.topLeft()-pos+size/2.);

	renderMap(painter, _game->map());
}

void GameRenderer::renderLayers(QPainter& painter, tmx::Map* map)
{
	renderLayerNamed(painter, map, "ground");
	renderLayerNamed(painter, map, "decoration");
	renderPlayer(painter, _game->player());
	renderLayerNamed(painter, map, "top");
	renderLayerNamed(painter, map, "walkable");
}

void GameRenderer::renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name)
{
	tmx::Layer* layer = map->layerNamed(name);
	if (layer) renderLayer(painter, layer);
	else qDebug() << name;
}

void GameRenderer::renderPlayer(QPainter& painter, Player* player)
{
	painter.save();
	painter.translate(_mapOffset+_viewport.topLeft());
	QPoint pos = player->position().toPoint();
	painter.fillRect(player->rect(), Qt::green);
	painter.fillRect(player->marginedRect(), Qt::red);
	painter.restore();
}
