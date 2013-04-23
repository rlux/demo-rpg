#include <Engine.h>

#include <qmath.h>
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
	Player* player = _game->player();
	moveObject(player, delta);
}

void Engine::moveObject(AnimatedObject* object, double delta)
{
	const QSize& tileSize = _game->map()->tileSize();

	double velocity = object->velocity();

	double d = velocity*delta;

	QRectF rect = object->marginedRect();

	QList<double> steps;
	QPointF dir(0,0);

	switch (object->direction())
	{
		case AnimatedObject::Left:
			steps = splitStep(rect.left(), -d, tileSize.width());
			dir.setX(1);
			break;
		case AnimatedObject::Right:
			steps = splitStep(rect.right(), d, tileSize.width());
			dir.setX(1);
			break;
		case AnimatedObject::Up:
			steps = splitStep(rect.top(), -d, tileSize.height());
			dir.setY(1);
			break;
		case AnimatedObject::Down:
			steps = splitStep(rect.bottom(), d, tileSize.height());
			dir.setY(1);
			break;
	}

	QPointF pos = object->position();

	for (double step: steps)
	{
		QPointF dp = dir*step;
		if (canBeAt(object, pos+dp)) {
			pos+=dp;
		} else {
			break;
		}
	}

	object->setPosition(pos);
	object->animation()->update(delta);
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

	return true;
}

