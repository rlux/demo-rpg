#include <Game.h>

#include <MapEvent.h>

#include <QDebug>

Game::Game()
: _currentMap(nullptr)
{
}

Game::~Game()
{
	qDeleteAll(_maps);
}

Map* Game::currentMap()
{
	return _currentMap;
}

Player* Game::player()
{
	return &_player;
}

NPCFactory* Game::npcFactory()
{
	return &_npcFactory;
}

void Game::changeMap(const QString& map, const QString& target)
{
//	qDebug() << "change map"<<map<< target;
	_currentMap = obtainMap(map);
	_player.setPosition(_currentMap->target(target));
	emit(mapChanged());
}

void Game::handleKeyPress(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Left:
			_player.setDirection(Player::Left);
			_directions.insert(Player::Left);
			break;
		case Qt::Key_Right:
			_player.setDirection(Player::Right);
			_directions.insert(Player::Right);
			break;
		case Qt::Key_Up:
			_player.setDirection(Player::Up);
			_directions.insert(Player::Up);
			break;
		case Qt::Key_Down:
			_player.setDirection(Player::Down);
			_directions.insert(Player::Down);
			break;
	}
}

void Game::handleKeyRelease(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Left:
			_directions.remove(Player::Left);
			break;
		case Qt::Key_Right:
			_directions.remove(Player::Right);
			break;
		case Qt::Key_Up:
			_directions.remove(Player::Up);
			break;
		case Qt::Key_Down:
			_directions.remove(Player::Down);
			break;
	}
	if (_directions.isEmpty())
	{
		_player.setDirection(Player::None);
	}
	else if (!_directions.contains(_player.direction()))
	{
		_player.setDirection(*_directions.begin());
	}
}

void Game::processMapEvent(MapEvent* event)
{
	MapChangeEvent* e = dynamic_cast<MapChangeEvent*>(event);

	if (e) {
		changeMap(e->mapName(), e->target());
	}

	delete event;
}

Map* Game::obtainMap(const QString& name)
{
	if (!_maps.contains(name))
	{
		Map* map = new Map("data/maps/"+name+".tmx");
		map->initialize(_npcFactory);
		connect(map, SIGNAL(eventTriggered(MapEvent*)), this, SLOT(processMapEvent(MapEvent*)));
		_maps.insert(name, map);
	}

	return _maps[name];
}
