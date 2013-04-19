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
	qDeleteAll(_images);
}

void Renderer::loadResourcesFor(Map* map)
{
	QString path = QFileInfo(map->filename()).path();

	for (Tileset* tileset: map->tilesets())
	{
		//_tilesetImages.insert(tileset, loadImage(tileset->image()));
		loadImage(path, tileset->image());
	}
	for (ImageLayer* imageLayer: map->imageLayers())
	{
		//_images.insert(imageLayer, loadImage(imageLayer->image()));
		loadImage(path, imageLayer->image());
	}
}

void Renderer::loadImage(const QString& path, Image* image)
{
	QImage* img = new QImage(path+"/"+image->source());
	_images.insert(image, img);
}

void Renderer::renderMap(QPainter& painter, Map* map, const QRect& destRect)
{
	for (Layer* layer: map->layers())
	{
		renderLayer(painter, layer, destRect);
	}
}

void Renderer::renderLayer(QPainter& painter, Layer* layer, const QRect& destRect)
{
	if (!layer->isVisible()) return;
	if (layer->isTileLayer()) {
		renderTileLayer(painter, layer->asTileLayer(), destRect);
	} else if (layer->isImageLayer()) {
		renderImageLayer(painter, layer->asImageLayer(), destRect);
	}
}

void Renderer::renderTileLayer(QPainter& painter, TileLayer* layer, const QRect& destRect)
{
	const QSize& tileSize = layer->map()->tileSize();
	for (int y=0; y<layer->height(); ++y)
	{
		for (int x=0; x<layer->width(); ++x)
		{
			QRect target(QPoint(x*tileSize.width(), y*tileSize.height()), tileSize);
			Cell& cell = layer->cellAt(x, y);
			Tile* tile = cell.tile();
			if (tile)
			{
				QImage* image = _images[tile->tileset()->image()];
				if (image)
				{
					QRect rect = tile->rect();
					painter.drawImage(target, *image, rect);
				}
			}

			painter.drawRect(target);
		}
	}
}

void Renderer::renderImageLayer(QPainter& painter, ImageLayer* layer, const QRect& destRect)
{
	QImage* image = _images[layer->image()];
	if (image)
	{
		painter.drawImage(QPoint(), *image);
	}
}
