#pragma once

#include <QKeyEvent>
#include <QSet>
#include <QHash>
#include <QQueue>

#include <GameRenderer.h>
#include <Engine.h>
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

	void update(double delta);
	void render(QPainter& painter);

	void handleKeyPress(QKeyEvent* event);
	void handleKeyRelease(QKeyEvent* event);

	Map* currentMap();
	Player* player();
	NPCFactory* npcFactory();
	GameRenderer* renderer();

	void changeMap(const QString& map, const QString& target);
signals:
	void mapChanged();
protected slots:
	void queueMapEvent(MapEvent* event);
protected:
	Map* _currentMap;
	Player _player;
	QSet<Player::Direction> _directions;
	NPCFactory _npcFactory;
	QHash<QString, Map*> _maps;
	Engine* _engine;
	GameRenderer* _renderer;
	QQueue<MapEvent*> _mapEvents;

	void processMapEvents();
	void handleMapEvent(MapEvent* event);

	Map* obtainMap(const QString& name);
};
