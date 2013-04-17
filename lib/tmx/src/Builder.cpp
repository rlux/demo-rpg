#include <tmx/Builder.h>

#include <QDebug>

using namespace tmx;

void BuilderState::setAttribute(Format::Attribute attribute, const QString& value)
{
}

void BuilderState::handleData(const QString& data)
{
}

BuilderState* BuilderState::handleElement(Format::Element element)
{
	return new BuilderState();
}

BuilderState* StartState::handleElement(Format::Element element)
{
	if (element == Format::Map)
	{
		Map* map = new Map();
		maps << map;
		return new MapState(map);
	}
	else
	{
		return new BuilderState();
	}
}

MapState::MapState(Map* map) : map(map)
{
}

void MapState::setAttribute(Format::Attribute attribute, const QString& value)
{
	switch (attribute)
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

BuilderState* MapState::handleElement(Format::Element element)
{
	switch (element)
	{
		case Format::Tileset: {
			Tileset* tileset = new Tileset();
			map->addTileset(tileset);
			return new TilesetState(tileset);
		}
		case Format::Layer: {
			TileLayer* tileLayer = new TileLayer();
			map->addTileLayer(tileLayer);
			return new TileLayerState(tileLayer);
		}
		case Format::ObjectGroup:
			// todo
		default:
			return new BuilderState();
	}
}

TilesetState::TilesetState(Tileset* tileset) : tileset(tileset)
{
}

void TilesetState::setAttribute(Format::Attribute attribute, const QString& value)
{
	switch (attribute)
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

BuilderState* TilesetState::handleElement(Format::Element element)
{
	switch (element)
	{
		case Format::Image:
			return new ImageState(&tileset->image());
		case Format::TileOffset:
			return new TileOffsetState(&tileset->tileOffset());
		default:
			return new BuilderState();
	}
}

TileOffsetState::TileOffsetState(QPoint* tileOffset) : tileOffset(tileOffset)
{
}

void TileOffsetState::setAttribute(Format::Attribute attribute, const QString& value)
{
	switch (attribute)
	{
		case Format::X:
			tileOffset->setX(value.toInt());
			break;
		case Format::Y:
			tileOffset->setY(value.toInt());
			break;
	}
}

TileLayerState::TileLayerState(TileLayer* tileLayer) : tileLayer(tileLayer)
{
}

void TileLayerState::setAttribute(Format::Attribute attribute, const QString& value)
{
	switch (attribute)
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

BuilderState* TileLayerState::handleElement(Format::Element element)
{
	switch (element)
	{
		case Format::Data:
			return new DataState(&tileLayer->data());
		default:
			return new BuilderState();
	}
}


DataState::DataState(Data* data) : data(data)
{
}

void DataState::setAttribute(Format::Attribute attribute, const QString& value)
{
	switch (attribute)
	{
		case Format::Encoding:
			data->setEncoding(Data::encodingFromString(value));
			break;
		case Format::Compression:
			data->setCompression(Data::compressionFromString(value));
			break;
	}
}

void DataState::handleData(const QString& _data)
{
	data->setBytes(_data.toAscii());
}

ImageState::ImageState(Image* image) : image(image)
{
}

void ImageState::setAttribute(Format::Attribute attribute, const QString& value)
{
	switch (attribute)
	{
		case Format::ImageFormat:
			image->setFormat(value);
			break;
		case Format::Source:
			image->setSource(value);
			break;
		case Format::Trans:
			image->setTrans(value);
			break;
		case Format::Width:
			image->setWidth(value.toInt());
			break;
		case Format::Height:
			image->setHeight(value.toInt());
			break;
	}
}


Builder::Builder()
{
	_startState = new StartState();
}

Builder::~Builder()
{
	qDeleteAll(_stateStack);
	delete _startState;
}

Map* Builder::map() const
{
	return _startState->maps.first();
}

BuilderState* Builder::currentState()
{
	return _stateStack.isEmpty() ? _startState : _stateStack.top();
}

void Builder::create(const QString& type)
{
	Format::Element element = Format::element(type);

	BuilderState* state = currentState();
	_stateStack.push(state->handleElement(element));
}

void Builder::finish(const QString& type)
{
	Format::Element element = Format::element(type);

	delete _stateStack.pop();
}

void Builder::setAttribute(const QString& name, const QString& value)
{
	Format::Attribute attribute = Format::attribute(name);

	currentState()->setAttribute(attribute, value);
}

void Builder::data(const QString& bytes)
{
	currentState()->handleData(bytes);
}
