#pragma once

#include <tmx/Base.h>
#include <tmx/Tileset.h>
#include <tmx/TileMapper.h>
#include <tmx/TileLayer.h>
#include <tmx/ImageLayer.h>
#include <tmx/ObjectLayer.h>

#include <QSize>
#include <QList>

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

	QSize size() const;
	int width() const;
	int height() const;
	void setSize(const QSize& size);
	void setWidth(int width);
	void setHeight(int height);

	QSize tileSize() const;
	int tileWidth() const;
	int tileHeight() const;
	void setTileSize(const QSize& size);
	void setTileWidth(int width);
	void setTileHeight(int height);

	const TileMapper& tileMapper();
	void addTileset(Tileset* tileset);

	void addLayer(Layer* layer);

	QString toString() const;

	static Orientation orientationFromString(const QString& name);
protected:
	Orientation _orientation;
	QSize _size;
	QSize _tileSize;
//	QColor _backgroundColor;
	TileMapper _tileMapper;
	QList<Layer*> _layers;
};

} // namespace tmx
