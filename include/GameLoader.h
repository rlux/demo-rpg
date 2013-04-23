#pragma once

#include <Game.h>

#include <QDomElement>
#include <QString>

class GameLoader
{
public:
	GameLoader();

	Game* newGame();
protected:
	QString _path;

	Game* createGame(const QDomElement& element);
	void initializePlayer(const QDomElement& element, Player* player);
	void initializeAnimation(const QDomElement& element, Animation* animation);
};
