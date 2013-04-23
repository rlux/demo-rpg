#pragma once

#include <tmx/Map.h>

#include <QHash>
#include <QPainter>
#include <QRect>
#include <QPixmap>
#include <QPointF>

namespace tmx {

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void loadResourcesFor(Map* map);
	void setViewport(const QRect& viewport);
	const QRect& viewport() const;
	void setMapOffset(const QPointF& mapOffset);
	const QPointF& mapOffset() const;

	void renderMap(QPainter& painter, Map* map);
	void renderLayer(QPainter& painter, Layer* layer);
protected:
	QPixmap* _errorPixmap;
	QHash<Image*, QPixmap*> _pixmaps;
	QRect _viewport;
	QPointF _mapOffset;

	void loadImage(const QString& path, Image* image);

	virtual void renderBackground(QPainter& painter, Map* map);
	virtual void renderLayers(QPainter& painter, Map* map);

	void renderTileLayer(QPainter& painter, TileLayer* layer);
	void renderCell(QPainter& painter, const Cell& cell, const QRectF& area);
	void renderTile(QPainter& painter, Tile* tile, const QRectF& area);
	void renderImageLayer(QPainter& painter, ImageLayer* layer);
	void renderObjectLayer(QPainter& painter, ObjectLayer* layer);
	void renderObject(QPainter& painter, Object* object, const QColor& color, const QSize& tileSize);

	void renderError(QPainter& painter, const QRectF& area);
};

} // namespace tmx
