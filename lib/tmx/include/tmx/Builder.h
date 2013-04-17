#pragma once

#include <tmx/Format.h>
#include <tmx/Map.h>
#include <tmx/Tileset.h>
#include <tmx/TileLayer.h>

#include <QHash>
#include <QStack>
#include <QList>

namespace tmx {

class Builder
{
public:
	Builder();

	void create(const QString& type);
	void finish(const QString& type);
	void setAttribute(const QString& name, const QString& value);
	void data(const QString& bytes);

	Map* map() const;
protected:
	QStack<Format::Element> _elementStack;
	QStack<Map*> _mapStack;
	QStack<Tileset*> _tilesetStack;
	QStack<TileLayer*> _tileLayerStack;

	QList<Map*> _maps;

	Format::Element currentElementType() const;
	Map* currentMap();
	Tileset* currentTileset();
	TileLayer* currentTileLayer();

	void setMapAttribute(const QString& name, const QString& value);
	void setTilesetAttribute(const QString& name, const QString& value);
	void setTileOffsetAttribute(const QString& name, const QString& value);
	void setImageAttribute(const QString& name, const QString& value);
	void setTileLayerAttribute(const QString& name, const QString& value);
	void setTileLayerDataAttribute(const QString& name, const QString& value);
};


} // namespace tmx
