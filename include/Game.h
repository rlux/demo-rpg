#pragma once

#include <QKeyEvent>

#include <tmx/Map.h>

#include <Player.h>
#include <AnimatedObject.h>

class Game
{
public:
	Game();
	~Game();

	tmx::Map* map();

	Player* player();

	void handleKeyPress(QKeyEvent* event);
	void handleKeyRelease(QKeyEvent* event);
protected:
	tmx::Map* _map;
	Player* _player;
	QList<AnimatedObject*> _animatedObjects;
};
