#include <tmx/Renderer.h>

#include <QFileInfo>
#include <QImage>
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

void Renderer::loadImage(const QString& path, Image* image)
{
	_pixmaps.insert(image, new QPixmap(path+"/"+image->source()));
}

void Renderer::renderMap(QPainter& painter, Map* map)
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
}

void Renderer::renderTileLayer(QPainter& painter, TileLayer* layer)
{
	const QSize& tileSize = layer->map()->tileSize();

	for (int y=0; y<layer->height(); ++y)
	{
		for (int x=0; x<layer->width(); ++x)
		{
			QRect area(QPoint(x*tileSize.width(), y*tileSize.height()), tileSize);

			renderCell(painter, layer->cellAt(x, y), area);
			painter.drawRect(area);
		}
	}
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
		painter.drawPixmap(QPoint(), *pixmap);
	}
}
