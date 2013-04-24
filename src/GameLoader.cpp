#include <GameLoader.h>

#include <QDomDocument>
#include <QFileInfo>
#include <QDebug>

GameLoader::GameLoader()
{
}

Game* GameLoader::newGame()
{
	QString filename = "data/main.xml";

	QDomDocument document = load(filename);

	QDomElement node = document.documentElement();

	Game* game = createGame(node);

	_paths.pop();

	return game;
}

QString GameLoader::path()
{
	return _paths.top();
}

QDomDocument GameLoader::load(const QString& filename)
{
	QFile file(filename);
	QDomDocument document;

	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "couldn't open file" << filename;
	}
	if (!document.setContent(&file))
	{
		qDebug() << "error in file" << filename;
	}
	file.close();

	_paths.push(QFileInfo(filename).path());

	return document;
}

Game* GameLoader::createGame(const QDomElement& element)
{
	if (element.tagName()!="game") return nullptr;

	QString mapSource = element.attribute("startmap");
	Map* map = new Map(path()+"/"+mapSource);

	Game* game = new Game();
	initializeObject(element.firstChildElement("player"), game->player());

	QString spawnPoint = element.attribute("spawnpoint");
	QPoint pos;
	if (tmx::Layer* layer = map->internalMap()->layerNamed("spawn"))
	{
		if (tmx::ObjectLayer* oLayer = layer->asObjectLayer())
		{
			if (tmx::Object* o = oLayer->objectNamed(spawnPoint))
			{
				pos = o->position();
			}
		}
	}
	game->player()->setPosition(pos);

	QDomNodeList children = element.childNodes();
	for (int i=0; i<children.size(); ++i)
	{
		QDomElement child = children.at(i).toElement();
		if (child.tagName()=="npcs")
		{
			for (NPC* npc: loadNpcs(child))
			{
				game->npcFactory()->addPrototype(npc->name(), npc);
			}
		}
	}

	game->setCurrentMap(map);

	return game;
}

void GameLoader::initializeObject(const QDomElement& element, AnimatedObject* object)
{
	QSize size(element.attribute("width").toUInt(), element.attribute("height").toUInt());
	double velocity = element.attribute("velocity").toDouble();

	object->setSize(size);
	object->setVelocity(velocity);

	QDomElement marginsElement = element.firstChildElement("margins");
	QMargins margins(marginsElement.attribute("left").toInt(), marginsElement.attribute("top").toInt(), marginsElement.attribute("right").toInt(), marginsElement.attribute("bottom").toInt());
	object->setMargins(margins);

	initializeAnimation(element.firstChildElement("animation"), object->animation());
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
	animation->setImage(path()+"/"+image);
}

QList<NPC*> GameLoader::loadNpcs(const QDomElement& element)
{
	QList<NPC*> npcs;
	QString source = element.attribute("source");
	if (!source.isNull())
	{
		QDomDocument document = load(path()+"/"+source);
		npcs = loadNpcs(document.documentElement());
		_paths.pop();
		return npcs;
	}

	QDomNodeList children = element.childNodes();
	for (int i=0; i<children.size(); ++i)
	{
		QDomElement child = children.at(i).toElement();
		if (child.tagName()=="npc")
		{
			NPC* npc = new NPC();
			npc->setName(child.attribute("name"));
			initializeObject(child, npc);
			npcs << npc;
		}
	}

	return npcs;
}

