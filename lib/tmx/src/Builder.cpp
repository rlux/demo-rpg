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
		case Format::Layer:{
			TileLayer* tileLayer = new TileLayer();
			_tileLayerStack.push(tileLayer);
			currentMap()->addTileLayer(tileLayer);
			break;
		}
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
			_tileLayerStack.pop();
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
	if (_mapStack.isEmpty()) return nullptr;
	return _mapStack.top();
}

Tileset* Builder::currentTileset()
{
	if (_tilesetStack.isEmpty()) return nullptr;
	return _tilesetStack.top();
}

TileLayer* Builder::currentTileLayer()
{
	if (_tileLayerStack.isEmpty()) return nullptr;
	return _tileLayerStack.top();
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
		case Format::Image:
			setImageAttribute(name, value);
			break;
		case Format::Layer:
			setTileLayerAttribute(name, value);
			break;
		case Format::Data:
			setTileLayerDataAttribute(name, value);
			break;
	}
}

void Builder::data(const QString& string)
{
	if (currentElementType()==Format::Data)
	{
		currentTileLayer()->data().setBytes(string.toAscii());
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

void Builder::setImageAttribute(const QString& name, const QString& value)
{
	Tileset* tileset = currentTileset();

	if (!tileset) return; // image layer

	switch (Format::attribute(name))
	{
		case Format::ImageFormat:
			tileset->image().setFormat(value);
			break;
		case Format::Source:
			tileset->image().setSource(value);
			break;
		case Format::Trans:
			tileset->image().setTrans(value);
			break;
		case Format::Width:
			tileset->image().setWidth(value.toInt());
			break;
		case Format::Height:
			tileset->image().setHeight(value.toInt());
			break;
	}
}

void Builder::setTileLayerAttribute(const QString& name, const QString& value)
{
	TileLayer* tileLayer = currentTileLayer();

	switch (Format::attribute(name))
	{
		case Format::Name:
			tileLayer->setName(value);
			break;
		case Format::X:
			tileLayer->setX(value.toInt());
			break;
		case Format::Y:
			tileLayer->setY(value.toInt());
			break;
		case Format::Width:
			tileLayer->setWidth(value.toInt());
			break;
		case Format::Height:
			tileLayer->setHeight(value.toInt());
			break;
		case Format::Opacity:
			tileLayer->setOpacity(value.toFloat());
			break;
		case Format::Visible:
			tileLayer->setVisible(value.toInt()!=0);
			break;
	}
}

void Builder::setTileLayerDataAttribute(const QString& name, const QString& value)
{
	TileLayer* tileLayer = currentTileLayer();

	switch (Format::attribute(name))
	{
		case Format::Encoding:
			tileLayer->data().setEncoding(Data::encodingFromString(value));
			break;
		case Format::Compression:
			tileLayer->data().setCompression(Data::compressionFromString(value));
			break;
	}
}
