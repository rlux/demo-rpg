#pragma once

#include <QMainWindow>
#include <QString>
#include <QPaintEvent>
#include <QKeyEvent>

#include <tmx/Renderer.h>

class MainWindow : public QMainWindow
{
public:
	MainWindow();

	void load(const QString& filename);

	virtual void paintEvent(QPaintEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
protected:
	tmx::Map* _map;
	tmx::Renderer _renderer;

	void moveMap(int dx, int dy);
};
