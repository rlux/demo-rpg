#pragma once

#include <tmx/Map.h>

#include <QHash>
#include <QPainter>
#include <QRect>

namespace tmx {

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void loadResourcesFor(Map* map);

	void renderMap(QPainter& painter, Map* map, const QRect& destRect);
	void renderLayer(QPainter& painter, Layer* layer, const QRect& destRect);
protected:
	QHash<Image*, QImage*> _images;

	void loadImage(const QString& path, Image* image);

	void renderTileLayer(QPainter& painter, TileLayer* layer, const QRect& destRect);
	void renderImageLayer(QPainter& painter, ImageLayer* layer, const QRect& destRect);
//	virtual void renderObjects(QPainter& painter, const QRect& mapRect, const QRect& destRect);
};

} // namespace tmx
