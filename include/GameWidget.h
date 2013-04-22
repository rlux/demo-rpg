#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QTime>

#include <Game.h>
#include <GameRenderer.h>
#include <Engine.h>

class GameWidget : public QWidget
{
	Q_OBJECT
public:
	GameWidget(QWidget* parent = nullptr);
	~GameWidget();

	QSize sizeHint() const;

	virtual void paintEvent(QPaintEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void resizeEvent(QResizeEvent* event);
protected:
	Game* _game;
	GameRenderer* _renderer;
	Engine* _engine;
	QTime _time;
protected slots:
	void updateGame();
};
