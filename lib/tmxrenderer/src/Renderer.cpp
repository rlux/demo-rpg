#include <tmx/Renderer.h>

#include <QFileInfo>
#include <QImage>
#include <qmath.h>

#include <QDebug>

using namespace tmx;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	qDeleteAll(_pixmaps);
}

void Renderer::loadResourcesFor(Map* map)
{
	QString path = QFileInfo(map->filename()).path();

	for (Tileset* tileset: map->tilesets())
	{
		loadImage(path, tileset->image());
	}

	for (ImageLayer* imageLayer: map->imageLayers())
	{
		loadImage(path, imageLayer->image());
	}
}

void Renderer::setViewport(const QRect& viewport)
{
	_viewport = viewport;
}

const QRect& Renderer::viewport() const
{
	return _viewport;
}

void Renderer::setOffset(const QPoint& offset)
{
	_mapOffset = offset;
}

const QPoint& Renderer::offset() const
{
	return _mapOffset;
}

void Renderer::loadImage(const QString& path, Image* image)
{
	_pixmaps.insert(image, new QPixmap(path+"/"+image->source()));
}

void Renderer::renderMap(QPainter& painter, Map* map)
{
	painter.save();
	painter.setClipRect(_viewport);

	renderBackground(painter, map);
	renderLayers(painter, map);

	painter.restore();
}

void Renderer::renderBackground(QPainter& painter, Map* map)
{
	painter.fillRect(_viewport, map->backgroundColor());
}

void Renderer::renderLayers(QPainter& painter, Map* map)
{
	for (Layer* layer: map->layers())
	{
		if (layer->isVisible())
		{
			renderLayer(painter, layer);
		}
	}
}

void Renderer::renderLayer(QPainter& painter, Layer* layer)
{
	if (layer->isTileLayer())
	{
		renderTileLayer(painter, layer->asTileLayer());
	}
	else if (layer->isImageLayer())
	{
		renderImageLayer(painter, layer->asImageLayer());
	}
	else if (layer->isObjectLayer())
	{
		renderObjectLayer(painter, layer->asObjectLayer());
	}
}

void Renderer::renderTileLayer(QPainter& painter, TileLayer* layer)
{
	const QSize& tileSize = layer->map()->tileSize();

	QRect area = visibleTileArea(layer);

	for (int y=area.top(); y<area.bottom(); ++y)
	{
		for (int x=area.left(); x<area.right(); ++x)
		{
			QRect area(QPoint(x*tileSize.width(), y*tileSize.height())+_mapOffset+_viewport.topLeft(), tileSize);

			renderCell(painter, layer->cellAt(x, y), area);
		}
	}
}

QRect Renderer::visibleTileArea(TileLayer* layer)
{
	const QSize& tileSize = layer->map()->tileSize();

	int left = -_mapOffset.x()/tileSize.width();
	int top = -_mapOffset.y()/tileSize.height();
	int right = left+qCeil((float)_viewport.width()/tileSize.width());
	int bottom = top+qCeil((float)_viewport.height()/tileSize.height());

	left = qBound(0, left, layer->width());
	right = qBound(0, right, layer->width());
	top = qBound(0, top, layer->height());
	bottom = qBound(0, bottom, layer->height());

	return QRect(QPoint(left, top), QPoint(right, bottom));
}

void Renderer::renderCell(QPainter& painter, const Cell& cell, const QRect& area)
{
	renderTile(painter, cell.tile(), area);
}

void Renderer::renderTile(QPainter& painter, Tile* tile, const QRect& area)
{
	if (!tile) return;

	QPixmap* pixmap = _pixmaps[tile->tileset()->image()];
	if (!pixmap) return;

	painter.drawPixmap(area, *pixmap, tile->rect());
}

void Renderer::renderImageLayer(QPainter& painter, ImageLayer* layer)
{
	QPixmap* pixmap = _pixmaps[layer->image()];
	if (pixmap)
	{
		painter.drawPixmap(_viewport.topLeft()+_mapOffset, *pixmap);
	}
}

void Renderer::renderObjectLayer(QPainter& painter, ObjectLayer* layer)
{
	for (Object* object: layer->objects())
	{
		renderObject(painter, object, layer->color());
	}
}

void Renderer::renderObject(QPainter& painter, Object* object, const QColor& color)
{
	QPoint pos = object->position()+_viewport.topLeft()+_mapOffset;

	painter.save();
	painter.translate(pos);
	painter.setBrush(QColor(color.red(), color.green(), color.blue(), 100));
	QPen pen(color);
	pen.setWidth(2);
	painter.setPen(pen);

	switch (object->shape())
	{
		case Object::Rectangle:
			painter.drawRect(QRect(QPoint(0,0), object->size()));
			break;
		case Object::Ellipse:
			painter.drawEllipse(QRect(QPoint(), object->size()));
			break;
		case Object::Polygon:
			painter.drawPolygon(object->points());
			break;
		case Object::Polyline:
			painter.drawPolyline(object->points());
			break;
		case Object::TileShape: {
			QRect rect(-QPoint(0,32), QSize(32,32));
			Tile* tile = object->tile();
			if (tile)
			{
				renderTile(painter, tile, rect);
			} else {
				painter.fillRect(rect, Qt::red);
			}
			break;
		}
	}

	painter.restore();
}

