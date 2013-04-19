#pragma once

#include <tmx/Map.h>

#include <QHash>
#include <QPainter>
#include <QRect>

namespace tmx {

class Renderer
{
public:
	Renderer(Map* map);
	virtual ~Renderer();

	void render(QPainter& painter, const QRect& destRect);
protected:
	Map* _map;
	QPoint _offset;
	QHash<Tileset*, QImage*> _tilesetImages;
	QHash<ImageLayer*, QImage*> _images;

	void loadImages();
	QImage* loadImage(Image& image);

	void renderLayer(QPainter& painter, Layer* layer, const QRect& destRect);
	void renderTileLayer(QPainter& painter, TileLayer* layer, const QRect& destRect);
	void renderImageLayer(QPainter& painter, ImageLayer* layer, const QRect& destRect);
//	virtual void renderObjects(QPainter& painter, const QRect& mapRect, const QRect& destRect);
};

} // namespace tmx
