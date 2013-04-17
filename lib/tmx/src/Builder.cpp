#include <tmx/Builder.h>

#include <QDebug>

using namespace tmx;

Builder::Builder()
{
}

Map* Builder::map() const
{
	return _maps.first();
}

void Builder::create(const QString& type)
{
	Format::Element element = Format::element(type);

	switch (element)
	{
		case Format::Map: {
			Map* map = new Map();
			_mapStack.push(map);
			_maps << map;
			break;
		}
		case Format::Tileset: {
			Tileset* tileset = new Tileset();
			_tilesetStack.push(tileset);
			currentMap()->addTileset(tileset);
			break;
		}
		case Format::Tile:
			break;
		case Format::Layer:
			break;
		case Format::ObjectGroup:
			break;
		case Format::Object:
			break;
	}

	_elementStack.push(element);
}

void Builder::finish(const QString& type)
{
	Format::Element element = Format::element(type);

	switch (element)
	{
		case Format::Map:
			_mapStack.pop();
			break;
		case Format::Tileset:
			_tilesetStack.pop();
			break;
		case Format::Tile:
			break;
		case Format::Layer:
			break;
		case Format::ObjectGroup:
			break;
		case Format::Object:
			break;
	}

	_elementStack.pop();
}

Format::Element Builder::currentElementType() const
{
	return _elementStack.top();
}

Map* Builder::currentMap()
{
	return _mapStack.top();
}

Tileset* Builder::currentTileset()
{
	return _tilesetStack.top();
}

void Builder::setAttribute(const QString& name, const QString& value)
{
	switch (currentElementType())
	{
		case Format::Map:
			setMapAttribute(name, value);
			break;
		case Format::Tileset:
			setTilesetAttribute(name, value);
			break;
		case Format::TileOffset:
			setTileOffsetAttribute(name, value);
			break;
	}
}

void Builder::setMapAttribute(const QString& name, const QString& value)
{
	Map* map = currentMap();

	switch (Format::attribute(name))
	{
		case Format::Version:
			// todo
			break;
		case Format::Orientation:
			map->setOrientation(Map::orientationFromString(value));
			break;
		case Format::Width:
			map->setWidth(value.toUInt());
			break;
		case Format::Height:
			map->setHeight(value.toUInt());
			break;
		case Format::TileWidth:
			map->setTileWidth(value.toUInt());
			break;
		case Format::TileHeight:
			map->setTileHeight(value.toUInt());
			break;
	}
}

void Builder::setTilesetAttribute(const QString& name, const QString& value)
{
	Tileset* tileset = currentTileset();

	switch (Format::attribute(name))
	{
		case Format::FirstGid:
			tileset->setFirstGid(value.toUInt());
			break;
		case Format::Source:
			tileset->setSource(value);
			break;
		case Format::Name:
			tileset->setName(value);
			break;
		case Format::Spacing:
			tileset->setSpacing(value.toInt());
			break;
		case Format::Margin:
			tileset->setMargin(value.toInt());
			break;
	}
}

void Builder::setTileOffsetAttribute(const QString& name, const QString& value)
{
	Tileset* tileset = currentTileset();

	switch (Format::attribute(name))
	{
		case Format::X:
			tileset->tileOffset().setX(value.toInt());
			break;
		case Format::Y:
			tileset->tileOffset().setY(value.toInt());
			break;
	}
}
