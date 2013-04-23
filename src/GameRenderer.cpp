#include <GameRenderer.h>
#include <Game.h>

#include <qmath.h>
#include <QDebug>

GameRenderer::GameRenderer(Game* game)
: _game(game)
{
}

void GameRenderer::renderGame(QPainter& painter)
{
	calculateOffset();
	renderMap(painter, _game->map());
}

void GameRenderer::calculateOffset()
{
	QPointF pos = _game->player()->position();
	QSizeF mapSize = _game->map()->pixelSize();

	double offsetX = _viewport.center().x()-pos.x();
	double offsetY = _viewport.center().y()-pos.y();

	if (mapSize.width()<_viewport.width()) {
		offsetX = _viewport.center().x()-mapSize.width()/2.0;
	} else {
		offsetX = -qBound(0.0, -offsetX, mapSize.width()-_viewport.width());
	}

	if (mapSize.height()<_viewport.height()) {
		offsetY = _viewport.center().y()-mapSize.height()/2.0;
	} else {
		offsetY = -qBound(0.0, -offsetY, mapSize.height()-_viewport.height());
	}

	setMapOffset(QPointF(offsetX, offsetY));
}

void GameRenderer::renderLayers(QPainter& painter, tmx::Map* map)
{
	renderLayerNamed(painter, map, "ground");
	renderLayerNamed(painter, map, "decoration");
	renderObject(painter, _game->player());
	renderLayerNamed(painter, map, "top");
	//renderLayerNamed(painter, map, "walkable");
}

void GameRenderer::renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name)
{
	tmx::Layer* layer = map->layerNamed(name);
	if (layer) renderLayer(painter, layer);
}

void GameRenderer::renderObject(QPainter& painter, AnimatedObject* object)
{
	painter.save();
	painter.translate(_mapOffset+_viewport.topLeft());

	//painter.fillRect(object->marginedRect(), Qt::blue);

	QPixmap* pixmap = object->animation()->pixmap();
	if (pixmap)
	{
		painter.drawPixmap(object->rect(), *pixmap, object->animation()->rect());
	}
	else
	{
		renderError(painter, object->rect());
	}

	painter.restore();
}
