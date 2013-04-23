#include <GameLoader.h>

#include <tmx/Loader.h>

#include <QDomDocument>
#include <QFileInfo>
#include <QDebug>

GameLoader::GameLoader()
{
}

Game* GameLoader::newGame()
{
	QFile file("data/main.xml");
	QDomDocument document;

	if (!file.open(QIODevice::ReadOnly)) {
		return nullptr;
	}
	if (!document.setContent(&file)) {
		file.close();
		return nullptr;
	}
	file.close();

	_path = QFileInfo(file).path();

	QDomElement node = document.documentElement();

	return createGame(node);
}

Game* GameLoader::createGame(const QDomElement& element)
{
	if (element.tagName()!="game") return nullptr;

	QString mapSource = element.attribute("startmap");
	tmx::Map* map = tmx::Loader::loadMap(_path+"/"+mapSource);

	if (!map) return nullptr;

	Game* game = new Game(map);
	initializePlayer(element.firstChildElement("player"), game->player());

	QString spawnPoint = element.attribute("spawnpoint");
	QPoint pos;
	if (tmx::Layer* layer = map->layerNamed("spawn")) {
		if (tmx::ObjectLayer* oLayer = layer->asObjectLayer()) {
			if (tmx::Object* o = oLayer->objectNamed(spawnPoint)) {
				pos = o->position();
			}
		}
	}
	game->player()->setPosition(pos);

	return game;
}

void GameLoader::initializePlayer(const QDomElement& element, Player* player)
{
	QSize size(element.attribute("width").toUInt(), element.attribute("height").toUInt());
	double velocity = element.attribute("velocity").toDouble();

	player->setSize(size);
	player->setVelocity(velocity);

	QDomElement marginsElement = element.firstChildElement("margins");
	QMargins margins(marginsElement.attribute("left").toInt(), marginsElement.attribute("top").toInt(), marginsElement.attribute("right").toInt(), marginsElement.attribute("bottom").toInt());
	player->setMargins(margins);

	initializeAnimation(element.firstChildElement("animation"), player->animation());
}

void GameLoader::initializeAnimation(const QDomElement& element, Animation* animation)
{
	QSize size(element.attribute("width").toUInt(), element.attribute("height").toUInt());
	double duration = element.attribute("duration").toDouble();
	QList<unsigned> steps;
	for (const QString& step: element.attribute("steps").split(' '))
	{
		steps << step.toUInt();
	}
	QString image = element.attribute("image");
	QString layout = element.attribute("layout");
	for (int i=0; i<layout.size(); ++i)
	{
		switch (layout[i].toLower().toAscii())
		{
			case 'l':
				animation->setOffset(Animation::Left, i);
				break;
			case 'r':
				animation->setOffset(Animation::Right, i);
				break;
			case 'u':
				animation->setOffset(Animation::Up, i);
				break;
			case 'd':
				animation->setOffset(Animation::Down, i);
				break;
		}
	}

	animation->setSize(size);
	animation->setDuration(duration);
	animation->setSteps(steps);
	animation->setImage(_path+"/"+image);
}
