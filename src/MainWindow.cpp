#include <MainWindow.h>
#include <GameWidget.h>

using namespace tmx;

MainWindow::MainWindow()
{
	GameWidget* gameWidget = new GameWidget(this);
	setCentralWidget(gameWidget);
}
