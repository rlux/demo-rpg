#pragma once

#include <tmx/Map.h>

#include <Player.h>

class Game
{
public:
	Game();
	~Game();

	tmx::Map* map();

	Player* player();
protected:
	tmx::Map* _map;
	Player _player;
};
