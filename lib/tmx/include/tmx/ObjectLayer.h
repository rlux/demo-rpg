#pragma once

#include <tmx/Layer.h>

namespace tmx {

class ObjectLayer : public Layer
{
public:
	virtual bool isObjectLayer() const;

	QString toString() const;
protected:

};

} // namespace tmx
