#pragma once

#include <tmx/Base.h>
#include <tmx/Tileset.h>
#include <tmx/TileMapper.h>
#include <tmx/TileLayer.h>
#include <tmx/ImageLayer.h>
#include <tmx/ObjectLayer.h>

#include <QSize>
#include <QList>
#include <QColor>

namespace tmx {

class Map : public Base
{
public:
	enum Orientation {
		Invalid,
		Orthogonal,
		Isometric,
		Staggered
	};

	Map();
	Map(Orientation orientation, const QSize& size, const QSize& tileSize);

	~Map();

	Orientation orientation() const;
	void setOrientation(Orientation orientation);

	const QSize& size() const;
	int width() const;
	int height() const;
	void setSize(const QSize& size);
	void setWidth(int width);
	void setHeight(int height);

	const QSize& tileSize() const;
	int tileWidth() const;
	int tileHeight() const;
	void setTileSize(const QSize& size);
	void setTileWidth(int width);
	void setTileHeight(int height);

	void setFilename(const QString& filename);
	const QString& filename() const;

	const QColor& backgroundColor() const;
	void setBackgroundColor(const QColor& color);

	const TileMapper& tileMapper() const;
	void addTileset(Tileset* tileset);
	const QList<Tileset*>& tilesets() const;

	void addLayer(Layer* layer);
	const QList<Layer*>& layers() const;
	QList<TileLayer*> tileLayers() const;
	QList<ImageLayer*> imageLayers() const;
	QList<ObjectLayer*> objectLayers() const;
	Layer* layerNamed(const QString& name) const;

	QString toString() const;

	static Orientation orientationFromString(const QString& name);
protected:
	Orientation _orientation;
	QSize _size;
	QSize _tileSize;
	QColor _backgroundColor;
	TileMapper _tileMapper;
	QList<Layer*> _layers;
	QString _filename;
};

} // namespace tmx
