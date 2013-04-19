#pragma once

#include <tmx/Map.h>

#include <QHash>
#include <QPainter>
#include <QRect>
#include <QPixmap>

namespace tmx {

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void loadResourcesFor(Map* map);

	void renderMap(QPainter& painter, Map* map);
	void renderLayer(QPainter& painter, Layer* layer);
protected:
	QHash<Image*, QPixmap*> _pixmaps;
	QRect _viewport;

	void loadImage(const QString& path, Image* image);

	void renderTileLayer(QPainter& painter, TileLayer* layer);
	void renderCell(QPainter& painter, const Cell& cell, const QRect& area);
	void renderImageLayer(QPainter& painter, ImageLayer* layer);
//	virtual void renderObjects(QPainter& painter, const QRect& mapRect, const QRect& destRect);
};

} // namespace tmx
