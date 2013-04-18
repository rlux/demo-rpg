#pragma once

#include <tmx/Map.h>

#include <QString>

namespace tmx {

class Parser
{
public:
	Parser();

	void parseFile(const QString& filename);

	Map* map();
protected:
	Map* _map;
};

} // namespace tmx
