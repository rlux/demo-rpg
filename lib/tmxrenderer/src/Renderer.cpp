#include <tmx/Renderer.h>

#include <QFileInfo>
#include <QImage>
#include <QDebug>

using namespace tmx;

Renderer::Renderer(Map* map)
: _map(map)
{
	loadImages();
}

Renderer::~Renderer()
{
	qDeleteAll(_tilesetImages);
	qDeleteAll(_images);
}

void Renderer::loadImages()
{
	for (Tileset* tileset: _map->tilesets())
	{
		_tilesetImages.insert(tileset, loadImage(tileset->image()));
	}
	for (ImageLayer* imageLayer: _map->imageLayers())
	{
		_images.insert(imageLayer, loadImage(imageLayer->image()));
	}
}

QImage* Renderer::loadImage(Image& image)
{
	QString path = QFileInfo(_map->filename()).path();
	return new QImage(path+"/"+image.source());
}

void Renderer::render(QPainter& painter, const QRect& destRect)
{
	for (Layer* layer: _map->layers())
	{
		if (!layer->isVisible()) continue;
		if (layer->isTileLayer()) {
			renderTileLayer(painter, layer->asTileLayer(), destRect);
		} else if (layer->isImageLayer()) {
			renderImageLayer(painter, layer->asImageLayer(), destRect);
		}
	}
}

void Renderer::renderTileLayer(QPainter& painter, TileLayer* layer, const QRect& destRect)
{
	const QSize& tileSize = _map->tileSize();
	for (int y=0; y<layer->height(); ++y)
	{
		for (int x=0; x<layer->width(); ++x)
		{
			Cell& cell = layer->cellAt(x, y);
			Tile* tile = cell.tile();
			if (!tile) continue;
			QImage* image = _tilesetImages[tile->tileset()];
			QRect rect = tile->rect();

			QRect target(QPoint(x*tileSize.width(), y*tileSize.height()), tileSize);

			painter.drawImage(target, *image, rect);
			painter.drawRect(target);
		}
	}
}

void Renderer::renderImageLayer(QPainter& painter, ImageLayer* layer, const QRect& destRect)
{
	QImage* image = _images[layer];
	painter.drawImage(QPoint(), *image);
}
