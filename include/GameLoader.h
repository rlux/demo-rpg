#pragma once

#include <Game.h>

#include <QDomDocument>
#include <QString>
#include <QStack>

class GameLoader
{
public:
	GameLoader();

	Game* newGame();
protected:
	QStack<QString> _paths;

	QString path();

	QDomDocument load(const QString& filename);

	Game* createGame(const QDomElement& element);
	void initializeObject(const QDomElement& element, AnimatedObject* object);
	void initializeAnimation(const QDomElement& element, Animation* animation);
	QList<NPC*> loadNpcs(const QDomElement& element);
};
