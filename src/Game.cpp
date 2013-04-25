#include <Game.h>

#include <MapEvent.h>

#include <QApplication>
#include <QDebug>

Game::Game()
: _currentMap(nullptr)
, _engine(new Engine(this))
, _renderer(new GameRenderer(this))
{
}

Game::~Game()
{
	qDeleteAll(_maps);
	delete _engine;
	delete _renderer;
}

void Game::update(double delta)
{
	_engine->update(delta);
}

void Game::render(QPainter& painter)
{
	_renderer->renderGame(painter);
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
		case Qt::Key_1:
			_renderer->toggleRenderFlag(GameRenderer::RenderEvents);
			break;
		case Qt::Key_2:
			_renderer->toggleRenderFlag(GameRenderer::RenderWalkable);
			break;
		case Qt::Key_3:
			_renderer->toggleRenderFlag(GameRenderer::RenderCollisionVolume);
			break;
		case Qt::Key_Escape:
			QApplication::quit();
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
	if (MapChangeEvent* e = dynamic_cast<MapChangeEvent*>(event))
	{
		changeMap(e->mapName(), e->target());
	}
	else if (TeleportEvent* e = dynamic_cast<TeleportEvent*>(event))
	{
		_currentMap->moveObjectToTarget(e->trigger(), e->target());
	}

	delete event;
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

GameRenderer* Game::renderer()
{
	return _renderer;
}

void Game::changeMap(const QString& map, const QString& target)
{
	_currentMap = obtainMap(map);
	_currentMap->moveObjectToTarget(&_player, target);
	emit(mapChanged());
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
