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
	const QSize& tileSize = _game->map()->tileSize();

	double velocity = player->velocity();
	QPointF pos = player->position();

	double d = velocity*delta;

	QPointF newPos = pos;
	switch (player->direction())
	{
		case Player::Left:
			newPos.setX(pos.x()-d);
			break;
		case Player::Right:
			newPos.setX(pos.x()+d);
			break;
		case Player::Up:
			newPos.setY(pos.y()-d);
			break;
		case Player::Down:
			newPos.setY(pos.y()+d);
			break;
	}

	if (canMoveTo(player, newPos))
	{
		player->setPosition(newPos);
	}
	else
	{
		int margin = player->margin();
		QRectF rect = player->rect().adjusted(margin,margin,-margin,-margin);
		switch (player->direction())
		{
			case Player::Left:
				rect.moveLeft(qFloor(rect.left()/tileSize.width())*tileSize.width());
				break;
			case Player::Right:
				rect.moveRight(qCeil(rect.right()/tileSize.width())*tileSize.width());
				break;
			case Player::Up:
				rect.moveTop(qFloor(rect.top()/tileSize.height())*tileSize.height());
				break;
			case Player::Down:
				rect.moveBottom(qCeil(rect.bottom()/tileSize.height())*tileSize.height());
				break;
		}
		player->setPosition(rect.topLeft()-QPoint(margin, margin));
	}
}

tmx::TileLayer* Engine::walkableLayer()
{
	tmx::Layer* layer = _game->map()->layerNamed("walkable");
	return layer ? layer->asTileLayer() : nullptr;
}

bool Engine::inMap(const QRectF& rect)
{
	QSize size = _game->map()->size();
	return true;
}

bool Engine::canMoveTo(AnimatedObject* object, const QPointF& pos)
{
	int margin = object->margin();
	QRectF rect = QRectF(pos, object->size()).adjusted(margin,margin,-margin,-margin);

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

