#include <Game.h>

#include <QDebug>

Game::Game()
: _map(nullptr)
{
}

Game::~Game()
{
	delete _map;
}

Map* Game::currentMap()
{
	return _map;
}

void Game::setCurrentMap(Map* map)
{
	_map = map;
	_map->initialize(_npcFactory);
}

Player* Game::player()
{
	return &_player;
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
			_player.setDirection(Player::Left);
			_directions.insert(Player::Left);
			break;
		case Qt::Key_Right:
			_player.setDirection(Player::Right);
			_directions.insert(Player::Right);
			break;
		case Qt::Key_Up:
			_player.setDirection(Player::Up);
			_directions.insert(Player::Up);
			break;
		case Qt::Key_Down:
			_player.setDirection(Player::Down);
			_directions.insert(Player::Down);
			break;
		case Qt::Key_Backspace:
			_player.setPosition(QPointF(100,200));
			break;
	}
}

void Game::handleKeyRelease(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Left:
			_directions.remove(Player::Left);
			break;
		case Qt::Key_Right:
			_directions.remove(Player::Right);
			break;
		case Qt::Key_Up:
			_directions.remove(Player::Up);
			break;
		case Qt::Key_Down:
			_directions.remove(Player::Down);
			break;
	}
	if (_directions.isEmpty())
	{
		_player.setDirection(Player::None);
	}
	else if (!_directions.contains(_player.direction()))
	{
		_player.setDirection(*_directions.begin());
	}
}
