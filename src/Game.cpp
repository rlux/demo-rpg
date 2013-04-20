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

	_player.setPosition(pos);
}

Game::~Game()
{
	delete _map;
}

tmx::Map* Game::map()
{
	return _map;
}

Player* Game::player()
{
	return &_player;
}
