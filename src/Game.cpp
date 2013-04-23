#include <Game.h>

#include <tmx/Loader.h>

#include <QDebug>

Game::Game(tmx::Map* map)
: _map(map)
, _player(new Player())
{
	_animatedObjects << _player;
}

Game::~Game()
{
	qDeleteAll(_animatedObjects);
	delete _map;
}

tmx::Map* Game::map()
{
	return _map;
}

Player* Game::player()
{
	return _player;
}

const QList<AnimatedObject*>& Game::objects() const
{
	return _animatedObjects;
}

NPCFactory* Game::npcFactory()
{
	return &_npcFactory;
}

void Game::handleKeyPress(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Left:
			_player->setDirection(Player::Left);
			break;
		case Qt::Key_Right:
			_player->setDirection(Player::Right);
			break;
		case Qt::Key_Up:
			_player->setDirection(Player::Up);
			break;
		case Qt::Key_Down:
			_player->setDirection(Player::Down);
			break;
	}
}

void Game::handleKeyRelease(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Left:
			if (_player->direction()==Player::Left) _player->setDirection(Player::None);
			break;
		case Qt::Key_Right:
			if (_player->direction()==Player::Right) _player->setDirection(Player::None);
			break;
		case Qt::Key_Up:
			if (_player->direction()==Player::Up) _player->setDirection(Player::None);
			break;
		case Qt::Key_Down:
			if (_player->direction()==Player::Down) _player->setDirection(Player::None);
			break;
	}
}

void Game::initializeMap()
{
	if (tmx::Layer* layer = _map->layerNamed("objects"))
	{
		if (tmx::ObjectLayer* oLayer = layer->asObjectLayer())
		{
			for (tmx::Object* object: oLayer->objects())
			{
				if (object->type()=="npc") {
					QPointF pos = object->position();
					if (object->shape()==tmx::Object::TileShape) pos.setY(pos.y()-_map->tileSize().height());
					NPC* npc = _npcFactory.createNpc(object->name(), pos);
					_animatedObjects << npc;
				}
			}
		}
	}
}
