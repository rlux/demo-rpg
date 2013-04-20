#pragma once

#include <tmx/Map.h>

class Game
{
public:
	Game();
	~Game();

	tmx::Map* map();
protected:
	tmx::Map* _map;
};
