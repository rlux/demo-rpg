#include <MainWindow.h>

#include <tmx/Parser.h>

#include <QDebug>

using namespace tmx;

MainWindow::MainWindow()
: QMainWindow()
, _renderer(nullptr)
, _map(nullptr)
{
	resize(400,400);
}

void MainWindow::load(const QString& filename)
{
	Parser p;
	p.parseFile(filename);

	_map = p.map();

	_renderer = new Renderer(_map);

//	qDebug() << p.map()->toString();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QMainWindow::paintEvent(event);

	QPainter painter(this);

	if (_renderer) {
		_renderer->render(painter, rect());
	}
}
