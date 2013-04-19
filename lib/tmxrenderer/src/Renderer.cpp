#include <tmx/Renderer.h>

#include <QFileInfo>
#include <QImage>
#include <qmath.h>

#include <QDebug>

using namespace tmx;

Renderer::Renderer()
{
	_mapOffset = QPoint(-10,-10);
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

	for (Layer* layer: map->layers())
	{
		if (layer->isVisible())
		{
			renderLayer(painter, layer);
		}
	}

	painter.restore();
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
}

void Renderer::renderTileLayer(QPainter& painter, TileLayer* layer)
{
	const QSize& tileSize = layer->map()->tileSize();

	QRect area = visibleArea(layer);

	for (int y=area.top(); y<area.bottom(); ++y)
	{
		for (int x=area.left(); x<area.right(); ++x)
		{
			QRect area(QPoint(x*tileSize.width(), y*tileSize.height())+_mapOffset+_viewport.topLeft(), tileSize);

			renderCell(painter, layer->cellAt(x, y), area);
			painter.drawRect(area);
		}
	}
}

QRect Renderer::visibleArea(Layer* layer)
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
	Tile* tile = cell.tile();

	if (tile)
	{
		QPixmap* pixmap = _pixmaps[tile->tileset()->image()];
		if (pixmap)
		{
			QRect rect = tile->rect();
			painter.drawPixmap(area, *pixmap, rect);
		}
	}
}

void Renderer::renderImageLayer(QPainter& painter, ImageLayer* layer)
{
	QPixmap* pixmap = _pixmaps[layer->image()];
	if (pixmap)
	{
		painter.drawPixmap(_viewport.topLeft()+_mapOffset, *pixmap);
	}
}
