#include <Game.h>

#include <tmx/Loader.h>

Game::Game()
{
	_map = tmx::Loader::loadMap("data/example.tmx");
}

Game::~Game()
{
	delete _map;
}

tmx::Map* Game::map()
{
	return _map;
}
