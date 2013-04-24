#pragma once

#include <QKeyEvent>
#include <QList>

#include <tmx/Map.h>

#include <Player.h>
#include <NPC.h>
#include <NPCFactory.h>

class Game
{
public:
	Game(tmx::Map* map);
	~Game();

	tmx::Map* map();
	Player* player();
	const QList<AnimatedObject*>& objects() const;

	NPCFactory* npcFactory();

	void handleKeyPress(QKeyEvent* event);
	void handleKeyRelease(QKeyEvent* event);

	void initializeMap();
protected:
	tmx::Map* _map;
	Player* _player;
	QSet<Player::Direction> _directions;
	QList<AnimatedObject*> _animatedObjects;
	NPCFactory _npcFactory;
};
