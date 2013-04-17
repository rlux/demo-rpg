#include <tmx/Builder.h>

#include <QDebug>

using namespace tmx;
using namespace tmx::format;

void BuilderState::setAttribute(Attribute::Type attribute, const QString& value)
{
}

void BuilderState::handleData(const QString& data)
{
}

BuilderState* BuilderState::handleElement(Element::Type element)
{
	return new BuilderState();
}

BuilderState* DefaultState::handleElement(Element::Type element)
{
	// properties;
	return new BuilderState();
}

BuilderState* StartState::handleElement(Element::Type element)
{
	if (element == Element::Map)
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

void MapState::setAttribute(Attribute::Type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::Version:
			// todo
			break;
		case Attribute::Orientation:
			map->setOrientation(Map::orientationFromString(value));
			break;
		case Attribute::Width:
			map->setWidth(value.toUInt());
			break;
		case Attribute::Height:
			map->setHeight(value.toUInt());
			break;
		case Attribute::TileWidth:
			map->setTileWidth(value.toUInt());
			break;
		case Attribute::TileHeight:
			map->setTileHeight(value.toUInt());
			break;
	}
}

BuilderState* MapState::handleElement(Element::Type element)
{
	switch (element)
	{
		case Element::Tileset: {
			Tileset* tileset = new Tileset();
			map->addTileset(tileset);
			return new TilesetState(tileset);
		}
		case Element::Layer: {
			TileLayer* tileLayer = new TileLayer();
			map->addLayer(tileLayer);
			return new TileLayerState(tileLayer);
		}
		case Element::ImageLayer: {
			ImageLayer* imageLayer = new ImageLayer();
			map->addLayer(imageLayer);
			return new ImageLayerState(imageLayer);
		}
		case Element::ObjectGroup:{
			ObjectLayer* objectLayer = new ObjectLayer();
			map->addLayer(objectLayer);
			return new ObjectLayerState(objectLayer);
		}
		default:
			return DefaultState::handleElement(element);
	}
}

TilesetState::TilesetState(Tileset* tileset) : tileset(tileset)
{
}

void TilesetState::setAttribute(Attribute::Type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::FirstGid:
			tileset->setFirstGid(value.toUInt());
			break;
		case Attribute::Source:
			tileset->setSource(value);
			break;
		case Attribute::Name:
			tileset->setName(value);
			break;
		case Attribute::Spacing:
			tileset->setSpacing(value.toInt());
			break;
		case Attribute::Margin:
			tileset->setMargin(value.toInt());
			break;
	}
}

BuilderState* TilesetState::handleElement(Element::Type element)
{
	switch (element)
	{
		case Element::Image:
			return new ImageState(&tileset->image());
		case Element::TileOffset:
			return new TileOffsetState(&tileset->tileOffset());
		default:
			return DefaultState::handleElement(element);
	}
}

TileOffsetState::TileOffsetState(QPoint* tileOffset) : tileOffset(tileOffset)
{
}

void TileOffsetState::setAttribute(Attribute::Type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::X:
			tileOffset->setX(value.toInt());
			break;
		case Attribute::Y:
			tileOffset->setY(value.toInt());
			break;
	}
}

TileLayerState::TileLayerState(TileLayer* tileLayer) : tileLayer(tileLayer)
{
}

void TileLayerState::setAttribute(Attribute::Type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::Name:
			tileLayer->setName(value);
			break;
		case Attribute::X:
			tileLayer->setX(value.toInt());
			break;
		case Attribute::Y:
			tileLayer->setY(value.toInt());
			break;
		case Attribute::Width:
			tileLayer->setWidth(value.toInt());
			break;
		case Attribute::Height:
			tileLayer->setHeight(value.toInt());
			break;
		case Attribute::Opacity:
			tileLayer->setOpacity(value.toFloat());
			break;
		case Attribute::Visible:
			tileLayer->setVisible(value.toInt()!=0);
			break;
	}
}

BuilderState* TileLayerState::handleElement(Element::Type element)
{
	switch (element)
	{
		case Element::Data:
			return new DataState(&tileLayer->data());
		default:
			return DefaultState::handleElement(element);
	}
}

ImageLayerState::ImageLayerState(ImageLayer* imageLayer) : imageLayer(imageLayer)
{
}

BuilderState* ImageLayerState::handleElement(format::Element::Type element)
{
	switch (element)
	{
		case Element::Image:
			return new ImageState(&imageLayer->image());
		default:
			return DefaultState::handleElement(element);
	}
}

ObjectLayerState::ObjectLayerState(ObjectLayer* objectLayer) : objectLayer(objectLayer)
{
}

BuilderState* ObjectLayerState::handleElement(format::Element::Type element)
{
	switch (element)
	{
//		case Element::Image:
//			return new ImageState(&imageLayer->image());
		default:
			return DefaultState::handleElement(element);
	}
}

DataState::DataState(Data* data) : data(data)
{
}

void DataState::setAttribute(Attribute::Type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::Encoding:
			data->setEncoding(Data::encodingFromString(value));
			break;
		case Attribute::Compression:
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

void ImageState::setAttribute(Attribute::Type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::Format:
			image->setFormat(value);
			break;
		case Attribute::Source:
			image->setSource(value);
			break;
		case Attribute::Trans:
			image->setTrans(value);
			break;
		case Attribute::Width:
			image->setWidth(value.toInt());
			break;
		case Attribute::Height:
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

void Builder::create(const QString& elementName)
{
	_stateStack.push(currentState()->handleElement(Element::type(elementName)));
}

void Builder::finish(const QString& elementName)
{
	delete _stateStack.pop();
}

void Builder::setAttribute(const QString& attributeName, const QString& value)
{
	currentState()->setAttribute(Attribute::type(attributeName), value);
}

void Builder::data(const QString& bytes)
{
	currentState()->handleData(bytes);
}
