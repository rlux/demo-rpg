#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QResizeEvent>

#include <Game.h>
#include <GameRenderer.h>

class GameWidget : public QWidget
{
public:
	GameWidget(QWidget* parent = nullptr);
	~GameWidget();

	QSize sizeHint() const;

	virtual void paintEvent(QPaintEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void resizeEvent(QResizeEvent* event);
protected:
	Game* _game;
	GameRenderer _renderer;

	void moveMap(int dx, int dy);
};
