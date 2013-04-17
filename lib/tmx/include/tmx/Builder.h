#pragma once

#include <tmx/Format.h>
#include <tmx/Map.h>
#include <tmx/Tileset.h>

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

	Map* map() const;
protected:
	QStack<Format::Element> _elementStack;
	QStack<Map*> _mapStack;
	QStack<Tileset*> _tilesetStack;

	QList<Map*> _maps;

	Format::Element currentElementType() const;
	Map* currentMap();
	Tileset* currentTileset();

	void setMapAttribute(const QString& name, const QString& value);
	void setTilesetAttribute(const QString& name, const QString& value);
	void setTileOffsetAttribute(const QString& name, const QString& value);
};


} // namespace tmx
