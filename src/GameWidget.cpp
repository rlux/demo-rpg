#include <GameWidget.h>

#include <GameLoader.h>

#include <QTimer>
#include <QDebug>

GameWidget::GameWidget(QWidget* parent)
: QWidget(parent)
{
	_game = GameLoader().newGame();

	_renderer = new GameRenderer(_game);
	_renderer->setViewport(rect());

	_engine = new Engine(_game);

	setFocusPolicy(Qt::StrongFocus);

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
	_time.start();
	timer->start(20);
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

void GameWidget::updateGame()
{
	_engine->update(_time.elapsed()/1000.0);
	_time.restart();
	repaint();
}

void GameWidget::keyPressEvent(QKeyEvent* event)
{
	_game->handleKeyPress(event);
}

void GameWidget::keyReleaseEvent(QKeyEvent* event)
{
	_game->handleKeyRelease(event);
}

void GameWidget::resizeEvent(QResizeEvent* event)
{
	_renderer->setViewport(rect());
}

void GameWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	_renderer->renderGame(painter);
}
