#include <Engine.h>

#include <Game.h>

#include <qmath.h>
#include <QtAlgorithms>

#include <QDebug>

Engine::Engine(Game* game)
: _game(game)
{
	connect(_game, SIGNAL(mapChanged()), this, SLOT(mapChanged()));
}

void Engine::mapChanged()
{
}

void Engine::update(double delta)
{
	moveObjects(delta);
}

void Engine::moveObjects(double delta)
{
	if (_game->currentMap())
	{
		moveObject(_game->player(), delta);

		for (AnimatedObject* object: _game->currentMap()->objects())
		{
			moveObject(object, delta);
		}
	}
}

void Engine::moveObject(AnimatedObject* object, double delta)
{
	object->animation()->update(delta);

	if (object->direction()==AnimatedObject::None) return;

	double distance = object->velocity()*delta;

	QList<QPointF> points = wayPoints(object, distance);

	QSet<EventTrigger*> currentTriggers = _game->currentMap()->triggersIn(object->marginedRect());

	for (const QPointF point: points)
	{
		if (canBeAt(object, point) || !canBeAt(object, object->position()))
		{
			object->setPosition(point);
			checkTriggers(object, currentTriggers);
		}
		else
		{
			object->hitObstacle();
			break;
		}
	}
}

void Engine::checkTriggers(AnimatedObject* object, QSet<EventTrigger*>& currentTriggers)
{
	QSet<EventTrigger*> newTriggers = _game->currentMap()->triggersIn(object->marginedRect());

	if (object->isPlayer())
	{
		newTriggers.clear();
		for (EventTrigger* trigger: _game->currentMap()->triggersIn(object->marginedRect()))
		{
			if (trigger->intersects(object->marginedRect()))
			{
				newTriggers<<trigger;
			}
		}
	}


	for (EventTrigger* trigger: currentTriggers-newTriggers)
	{
		trigger->exit(object);
	}
	for (EventTrigger* trigger: newTriggers-currentTriggers)
	{
		trigger->enter(object);
	}

	currentTriggers = newTriggers;
}

tmx::TileLayer* Engine::walkableLayer()
{
	tmx::Layer* layer = _game->currentMap()->internalMap()->layerNamed("walkable");
	return layer ? layer->asTileLayer() : nullptr;
}

bool Engine::inMap(const QRectF& rect)
{
	if (rect.left()<0 || rect.top()<0) return false;
	const QSize& mapSize = _game->currentMap()->internalMap()->size();
	const QSize& tileSize = _game->currentMap()->internalMap()->tileSize();
	QSize size(mapSize.width()*tileSize.width(), mapSize.height()*tileSize.height());
	return rect.right()<=size.width() && rect.bottom()<=size.height();
}

bool Engine::canBeAt(AnimatedObject* object, const QPointF& pos)
{
	const QMargins& margins = object->margins();
	QRectF rect = QRectF(pos, object->size()).adjusted(margins.left(), margins.top(), margins.right(), margins.bottom());

	if (!inMap(rect)) return false;

	tmx::TileLayer* walkable = walkableLayer();
	if (!walkable) return true;

	QRect area = walkable->tileArea(rect);

	for (int y=area.top(); y<=area.bottom(); ++y)
	{
		for (int x=area.left(); x<=area.right(); ++x)
		{
			if (walkable->cellAt(x,y).tile()) return false;
		}
	}

	for (AnimatedObject* o: _game->currentMap()->objectsIn(rect))
	{
		if (o!=object) {
			return false;
		}
	}

	if (object!=_game->player() && _game->player()->marginedRect().intersects(rect)) return false;

	return true;
}

QList<QPointF> Engine::wayPoints(AnimatedObject* object, double distance)
{
	QList<QPointF> points;

	bool horizontal = object->direction()==AnimatedObject::Left || object->direction()==AnimatedObject::Right;
	bool ascending = object->direction()==AnimatedObject::Down || object->direction()==AnimatedObject::Right;

	QRectF rect = object->rect();
	QRectF start = object->marginedRect();
	QRectF goal = horizontal ? start.translated(ascending ? distance : -distance, 0) : start.translated(0, ascending ? distance : -distance);

	QRectF area = start.united(goal);

	QList<double> positions;
	for (const QRectF& obstacle: obstaclesIn(area, object))
	{
		if (horizontal) {
			positions << obstacle.left() << obstacle.right();
		} else {
			positions << obstacle.top() << obstacle.bottom();
		}
	}

	QSize mapSize = _game->currentMap()->internalMap()->pixelSize();
	if (horizontal) {
		positions << 0 << mapSize.width();
	} else {
		positions << 0 << mapSize.height();
	}

	if (ascending)
	{
		qSort(positions.begin(), positions.end(), qLess<double>());
	}
	else
	{
		qSort(positions.begin(), positions.end(), qGreater<double>());
	}

	double first = horizontal ? rect.left() : rect.top();
	double last = first + distance;
	double offset = ascending ? (horizontal ? rect.width() : rect.height()) : 0;

	points << rect.topLeft();

	for (double position: positions)
	{
		int value = position-offset;

		bool incorrect = (ascending ? value<first : value>first) || (ascending ? value>last : value<last);
		if (incorrect) {
			continue;
		}


		QPointF point = horizontal ? QPointF(value, rect.top()) : QPointF(rect.left(), value);

		points << point;
	}

	points << (horizontal ? rect.translated(ascending ? distance : -distance, 0) : rect.translated(0, ascending ? distance : -distance)).topLeft();


	return points;
}

QList<QRectF> Engine::obstaclesIn(const QRectF& area, AnimatedObject* object)
{
	QList<QRectF> obstacles;

	tmx::TileLayer* walkable = walkableLayer();
	QRect tileArea = walkable->tileArea(area);

	const QSize& tileSize = _game->currentMap()->internalMap()->tileSize();
	for (int y=tileArea.top(); y<=tileArea.bottom(); ++y)
	{
		for (int x=tileArea.left(); x<=tileArea.right(); ++x)
		{
			if (walkable->cellAt(x,y).tile())
			{
				QRect rect(QPoint(x*tileSize.width(), y*tileSize.height()), tileSize);
				obstacles << rect;
			}
		}
	}

	for (AnimatedObject* o: _game->currentMap()->objectsIn(area))
	{
		if (o!=object) {
			obstacles << o->rect();
		}
	}
	if (object!=_game->player() && _game->player()->marginedRect().intersects(area)) obstacles << _game->player()->marginedRect();

	for (EventTrigger* trigger: _game->currentMap()->triggersIn(area)) obstacles << trigger->rect();

	return obstacles;
}

