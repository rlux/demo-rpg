#include <GameRenderer.h>
#include <Game.h>

#include <qmath.h>
#include <QDebug>

GameRenderer::GameRenderer(Game* game)
: _game(game)
{
	loadResourcesFor(_game->currentMap()->internalMap());
}

void GameRenderer::renderGame(QPainter& painter)
{
	tmx::Map* map = _game->currentMap()->internalMap();
	if (map)
	{
		calculateOffset();
		renderMap(painter, map);
	}
}

void GameRenderer::calculateOffset()
{
	QPointF pos = _game->player()->position();
	QSizeF mapSize = _game->currentMap()->internalMap()->pixelSize();

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
	renderObjects(painter);
	renderLayerNamed(painter, map, "top");
	//renderLayerNamed(painter, map, "walkable");
}

void GameRenderer::renderLayerNamed(QPainter& painter, tmx::Map* map, const QString& name)
{
	tmx::Layer* layer = map->layerNamed(name);
	if (layer) renderLayer(painter, layer);
}

void GameRenderer::renderObjects(QPainter& painter)
{
	QList<AnimatedObject*> os = _game->currentMap()->objectsIn(QRect(-_mapOffset.toPoint(), _viewport.size()));
	os << _game->player();
	qSort(os.begin(), os.end(), [](const AnimatedObject* o1, const AnimatedObject* o2) {
		return o1->position().y()<o2->position().y();
	});
	for (AnimatedObject* object: os)
	{
		renderObject(painter, object);
	}
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
