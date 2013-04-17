#include <tmx/ObjectLayer.h>

using namespace tmx;


bool ObjectLayer::isObjectLayer() const
{
	return true;
}

QString ObjectLayer::toString() const
{
	return QString("ObjectLayer");
}
