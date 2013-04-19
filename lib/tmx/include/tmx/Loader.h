#pragma once

#include <tmx/Map.h>

#include <QString>

namespace tmx {

class Loader
{
public:
	static Map* loadMap(const QString& filename);
};

} // namespace tmx
