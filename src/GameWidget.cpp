#include <GameWidget.h>

#include <QDebug>

GameWidget::GameWidget(QWidget* parent)
: QWidget(parent)
{
	_game = new Game();
	_renderer = new GameRenderer(_game);
	_renderer->loadResourcesFor(_game->map());
	_renderer->setViewport(rect());

	setFocusPolicy(Qt::StrongFocus);
}

GameWidget::~GameWidget()
{
	delete _renderer;
	delete _game;
}

QSize GameWidget::sizeHint() const
{
	return QSize(800,600);
}

void GameWidget::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Left:
			movePlayer(-1,0);
			break;
		case Qt::Key_Right:
			movePlayer(1,0);
			break;
		case Qt::Key_Up:
			movePlayer(0,-1);
			break;
		case Qt::Key_Down:
			movePlayer(0,1);
			break;
	}
}

void GameWidget::resizeEvent(QResizeEvent* event)
{
	_renderer->setViewport(rect());
}

void GameWidget::movePlayer(int dx, int dy)
{
//	_renderer->setOffset(_renderer->offset()+QPoint(dx,dy)*10);
	_game->player()->setPosition(_game->player()->position()+QPoint(dx,dy)*32);
	repaint();
}


void GameWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	_renderer->renderGame(painter);
}
