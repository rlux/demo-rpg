#pragma once

#include <tmx/Base.h>

namespace tmx {

class TileLayer;
class ImageLayer;
class ObjectLayer;

class Layer : public Base
{
public:
	virtual bool isTileLayer() const;
	virtual bool isImageLayer() const;
	virtual bool isObjectLayer() const;

	TileLayer* asTileLayer();
	ImageLayer* asImageLayer();
	ObjectLayer* asObjectLayer();

	virtual QString toString() const = 0;
};

} // namespace tmx
