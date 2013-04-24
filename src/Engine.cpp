#include <Engine.h>

#include <qmath.h>
#include <QtAlgorithms>
#include <QDebug>

Engine::Engine(Game* game)
: _game(game)
{
}

void Engine::update(double delta)
{
	moveObjects(delta);
}

void Engine::moveObjects(double delta)
{
	if (_game->map())
	{
		Player* player = _game->player();
		moveObject(player, delta);
	}
}

void Engine::moveObject(AnimatedObject* object, double delta)
{
	const QSize& tileSize = _game->map()->tileSize();

	object->animation()->update(delta);

	if (object->direction()==AnimatedObject::None) return;

	double velocity = object->velocity();

	double distance = velocity*delta;

	QList<QPointF> points = wayPoints(object, distance);

	for (const QPointF point: points)
	{
		if (canBeAt(object, point))
		{
			object->setPosition(point);
		}
		else
		{
			break;
		}
	}

//	qDebug() << points;
//
//	QRectF rect = object->marginedRect();
//
//	QList<double> steps;
//	QPointF dir(0,0);
//
//	switch (object->direction())
//	{
//		case AnimatedObject::Left:
//			steps = splitStep(rect.left(), -distance, tileSize.width());
//			dir.setX(1);
//			break;
//		case AnimatedObject::Right:
//			steps = splitStep(rect.right(), distance, tileSize.width());
//			dir.setX(1);
//			break;
//		case AnimatedObject::Up:
//			steps = splitStep(rect.top(), -distance, tileSize.height());
//			dir.setY(1);
//			break;
//		case AnimatedObject::Down:
//			steps = splitStep(rect.bottom(), distance, tileSize.height());
//			dir.setY(1);
//			break;
//	}
//
//	QPointF pos = object->position();
//
//	for (double step: steps)
//	{
//		QPointF dp = dir*step;
//		if (canBeAt(object, pos+dp)) {
//			pos+=dp;
//		} else {
//			break;
//		}
//	}
//
//	object->setPosition(pos);
}

QList<double> Engine::splitStep(double start, double d, double step)
{
	QList<double> steps;

	if (d<0)
	{
		steps = splitStep(-start, -d, step);
		for (int i=0;i<steps.size();++i)
		steps[i] *= -1;
		return steps;
	}

	double next = step * qCeil(start/step);

	if (next>start + d)
	{
		steps << d;
	}
	else
	{
		steps << next - start;
		int f = (start + d - next)/step;
		for (int i=0;i<f;++i) steps << step;
		int remainder = start + d - (next + f*step);
		if (remainder>0) steps << remainder;
	}

	return steps;
}

tmx::TileLayer* Engine::walkableLayer()
{
	tmx::Layer* layer = _game->map()->layerNamed("walkable");
	return layer ? layer->asTileLayer() : nullptr;
}

bool Engine::inMap(const QRectF& rect)
{
	if (rect.left()<0 || rect.top()<0) return false;
	const QSize& mapSize = _game->map()->size();
	const QSize& tileSize = _game->map()->tileSize();
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

	for (AnimatedObject* o: objectsIn(rect))
	{
		if (o!=object) {
			return false;
		}
	}

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

	if (ascending)
	{
		qSort(positions.begin(), positions.end(), qLess<double>());
	}
	else
	{
		qSort(positions.begin(), positions.end(), qGreater<double>());
	}

	double first = horizontal ? rect.left() : rect.top();
	double offset = ascending ? (horizontal ? rect.width() : rect.height()) : 0;

	points << rect.topLeft();

	for (double position: positions)
	{
		int value = position-offset;

		bool incorrect = ascending ? value<first : value>first;
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

	const QSize& tileSize = _game->map()->tileSize();
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

	for (AnimatedObject* o: objectsIn(area))
	{
		if (o!=object) {
			obstacles << o->rect();
		}
	}

	return obstacles;
}

QList<AnimatedObject*> Engine::objectsIn(const QRectF& area)
{
	QList<AnimatedObject*> objects;

	for (AnimatedObject* o: _game->objects())
	{
		if (o->marginedRect().intersects(area))
		{
			objects << o;
		}
	}

	return objects;
}

