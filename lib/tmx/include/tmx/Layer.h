#pragma once

#include <tmx/Base.h>

#include <QSize>

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

	void setName(const QString& name);
	const QString& name() const;

	void setSize(const QSize& size);
	const QSize& size() const;
	void setWidth(int width);
	int width() const;
	void setHeight(int height);
	int height() const;

	void setOpacity(float opacity);
	float opacity() const;
	void setVisible(bool visible);
	bool isVisible() const;

	virtual QString toString() const = 0;
protected:
	Map* _map;
	QString _name;
	QSize _size;
	float _opacity;
	bool _visible;
};

} // namespace tmx
