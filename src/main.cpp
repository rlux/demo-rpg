#include <tmx/Parser.h>

using namespace tmx;

int main()
{
	Parser p;
	p.parseFile("data/example.tmx");

	return 0;
}
