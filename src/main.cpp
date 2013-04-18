#include <tmx/Parser.h>

#include <QDebug>

using namespace tmx;

int main()
{
	Parser p;
	p.parseFile("data/example.tmx");

	qDebug() << p.map()->toString();

	return 0;
}
