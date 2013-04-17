#include <tmx/ImageLayer.h>

using namespace tmx;

bool ImageLayer::isImageLayer() const
{
	return true;
}

Image& ImageLayer::image()
{
	return _image;
}

QString ImageLayer::toString() const
{
	return QString("ImageLayer(%1)").arg(_image.source());
}
