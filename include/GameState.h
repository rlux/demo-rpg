#pragma once

#include <QPainter>
#include <QKeyEvent>

class GameState
{
public:
	virtual void update(double delta);
	virtual void render(QPainter& painter);

	virtual void handleKeyPress(QKeyEvent* event);
	virtual void handleKeyRelease(QKeyEvent* event);
};
