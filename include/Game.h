#pragma once

#include <QKeyEvent>
#include <QList>

#include <Map.h>
#include <Player.h>
#include <NPC.h>
#include <NPCFactory.h>
#include <EventTrigger.h>

class Game
{
public:
	Game();
	~Game();

	void setCurrentMap(Map* map);

	Map* currentMap();
	Player* player();

	NPCFactory* npcFactory();

	void handleKeyPress(QKeyEvent* event);
	void handleKeyRelease(QKeyEvent* event);
protected:
	Map* _map;
	Player _player;
	QSet<Player::Direction> _directions;
	NPCFactory _npcFactory;
};
