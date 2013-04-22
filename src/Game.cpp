#include <Game.h>

#include <tmx/Loader.h>

#include <QDebug>

Game::Game()
{
	_map = tmx::Loader::loadMap("data/example.tmx");

	QPoint pos;
	if (tmx::Layer* layer = _map->layerNamed("spawn")) {
		if (tmx::ObjectLayer* oLayer = layer->asObjectLayer()) {
			if (tmx::Object* o = oLayer->objectNamed("player")) {
				pos = o->position();
			}
		}
	}

	_player = new Player();
	_player->setPosition(pos);
	_player->setVelocity(3*32);
}

Game::~Game()
{
	delete _player;
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
