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
	void setViewport(const QRect& viewport);
	const QRect& viewport() const;
	void setOffset(const QPoint& offset);
	const QPoint& offset() const;

	void renderMap(QPainter& painter, Map* map);
	void renderLayer(QPainter& painter, Layer* layer);
protected:
	QHash<Image*, QPixmap*> _pixmaps;
	QRect _viewport;
	QPoint _mapOffset;

	void loadImage(const QString& path, Image* image);

	void renderTileLayer(QPainter& painter, TileLayer* layer);
	QRect visibleArea(Layer* layer);
	void renderCell(QPainter& painter, const Cell& cell, const QRect& area);
	void renderImageLayer(QPainter& painter, ImageLayer* layer);
	void renderObjectLayer(QPainter& painter, ObjectLayer* layer);
	void renderObject(QPainter& painter, Object* object, const QColor& color);
};

} // namespace tmx
