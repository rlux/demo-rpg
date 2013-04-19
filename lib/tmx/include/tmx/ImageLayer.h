#pragma once

#include <tmx/Layer.h>
#include <tmx/Image.h>

namespace tmx {

class ImageLayer : public Layer
{
public:
	virtual bool isImageLayer() const;

	Image* image();

	QString toString() const;
protected:
	Image _image;
};

} // namespace tmx
