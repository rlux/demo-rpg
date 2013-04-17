#pragma once

#include <tmx/Base.h>

namespace tmx {

class TileLayer;
class ImageLayer;
class ObjectLayer;

class Map;

class Layer : public Base
{
public:
	Layer();

	Map* map() const;
	void setMap(Map* map);

	virtual bool isTileLayer() const;
	virtual bool isImageLayer() const;
	virtual bool isObjectLayer() const;

	TileLayer* asTileLayer();
	ImageLayer* asImageLayer();
	ObjectLayer* asObjectLayer();

	virtual QString toString() const = 0;
protected:
	Map* _map;
};

} // namespace tmx
