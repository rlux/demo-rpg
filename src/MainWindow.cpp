#include <MainWindow.h>

#include <tmx/Loader.h>

#include <QDebug>

using namespace tmx;

MainWindow::MainWindow()
: QMainWindow()
, _map(nullptr)
{
	resize(400,400);
}

void MainWindow::load(const QString& filename)
{
	_map = Loader::loadMap(filename);

	_renderer.loadResourcesFor(_map);
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QMainWindow::paintEvent(event);

	QPainter painter(this);

	int m = 20;
	QRect viewport = QRect(0,0,400,400).adjusted(m,m,-m,-m);

	_renderer.setViewport(viewport);
	_renderer.renderMap(painter, _map);

	painter.setPen(Qt::red);
	painter.drawRect(viewport);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Left:
			moveMap(-1,0);
			break;
		case Qt::Key_Right:
			moveMap(1,0);
			break;
		case Qt::Key_Up:
			moveMap(0,-1);
			break;
		case Qt::Key_Down:
			moveMap(0,1);
			break;
	}
}

void MainWindow::moveMap(int dx, int dy)
{
	_renderer.setOffset(_renderer.offset()+QPoint(dx,dy)*10);
	repaint();
}
