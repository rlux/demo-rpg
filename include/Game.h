#pragma once

#include <QKeyEvent>
#include <QSet>
#include <QHash>

#include <Map.h>
#include <Player.h>
#include <NPC.h>
#include <NPCFactory.h>
#include <EventTrigger.h>

class Game : public QObject
{
	Q_OBJECT
public:
	Game();
	~Game();

	Map* currentMap();
	Player* player();
	NPCFactory* npcFactory();

	void changeMap(const QString& map, const QString& target);

	void handleKeyPress(QKeyEvent* event);
	void handleKeyRelease(QKeyEvent* event);
signals:
	void mapChanged();
protected slots:
	void processMapEvent(MapEvent* event);
protected:
	Map* _currentMap;
	Player _player;
	QSet<Player::Direction> _directions;
	NPCFactory _npcFactory;
	QHash<QString, Map*> _maps;

	Map* obtainMap(const QString& name);
};
