#include <GameRenderer.h>
#include <Game.h>

#include <qmath.h>
#include <QDebug>

GameRenderer::GameRenderer(Game* game)
: _game(game)
, _debug(false)
{
	connect(_game, SIGNAL(mapChanged()), this, SLOT(mapChanged()));
}

void GameRenderer::mapChanged()
{
	if (_game->currentMap()->isValid())  loadResourcesFor(_game->currentMap()->internalMap());
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

void GameRenderer::setDebug(bool b)
{
	_debug = b;
}

bool GameRenderer::debug() const
{
	return _debug;
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
	if (_debug) renderEventTriggers(painter);
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
	QList<AnimatedObject*> os = _game->currentMap()->objectsIn(QRect(-_mapOffset.toPoint(), _viewport.size())).toList();
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

void GameRenderer::renderEventTriggers(QPainter& painter)
{
	for (EventTrigger* trigger: _game->currentMap()->triggers())
	{
		renderEventTrigger(painter, trigger);
	}
}

void GameRenderer::renderEventTrigger(QPainter& painter, EventTrigger* trigger)
{
	painter.save();
	QRectF rect = trigger->rect().translated(_mapOffset+_viewport.topLeft());
	QColor color(255, 100, 100);
	painter.fillRect(rect, QColor(color.red(), color.green(), color.blue(), 100));
	painter.setPen(color);
	painter.drawRect(rect);
	painter.setPen(Qt::white);
	QString name = trigger->name();
//	painter.drawText(rect, Qt::TextSingleLine, painter.fontMetrics().elidedText(name, Qt::ElideRight, rect.width()));
	painter.drawText(rect.topLeft()+QPointF(2,painter.fontMetrics().height()), name);
	painter.restore();
}
