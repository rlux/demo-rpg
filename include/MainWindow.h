#pragma once

#include <QMainWindow>
#include <QString>
#include <QPaintEvent>

#include <tmx/Renderer.h>

class MainWindow : public QMainWindow
{
public:
	MainWindow();

	void load(const QString& filename);

	virtual void paintEvent(QPaintEvent* event);
protected:
	tmx::Map* _map;
	tmx::Renderer* _renderer;
};
