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

//	qDebug() << p.map()->toString();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QMainWindow::paintEvent(event);

	QPainter painter(this);

	_renderer.renderMap(painter, _map, rect());
}
