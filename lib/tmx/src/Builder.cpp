#include <tmx/Builder.h>

#include <QDebug>

using namespace tmx;
using namespace tmx::format;


void BuilderState::handleAttribute(Attribute::Type attribute, const QString& value)
{
}

void BuilderState::handleData(const QString& data)
{
}

BuilderState* BuilderState::handleElement(Element::Type element)
{
	return new BuilderState();
}

void BuilderState::finish()
{
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

BaseState::BaseState(Base* base) : base(base)
{
}

BuilderState* BaseState::handleElement(Element::Type element)
{
	if (element == Element::Properties) {
		return new PropertiesState(base);
	} else {
		return new BuilderState();
	}
}

PropertiesState::PropertiesState(Base* base) : base(base)
{
}

void PropertiesState::handleAttribute(format::Attribute::Type attribute, const QString& value)
{
	qDebug() << value;
}

MapState::MapState(Map* map) : BaseState(map), map(map)
{
}

void MapState::handleAttribute(Attribute::Type attribute, const QString& value)
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
		case Attribute::BackgroundColor:
			map->setBackgroundColor(("FF"+value).toUInt(nullptr, 16));
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
			return BaseState::handleElement(element);
	}
}

TilesetState::TilesetState(Tileset* tileset) : BaseState(tileset), tileset(tileset)
{
}

void TilesetState::handleAttribute(Attribute::Type attribute, const QString& value)
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
		case Attribute::TileWidth:
			tileset->setTileWidth(value.toUInt());
			break;
		case Attribute::TileHeight:
			tileset->setTileHeight(value.toUInt());
			break;
	}
}

BuilderState* TilesetState::handleElement(Element::Type element)
{
	switch (element)
	{
		case Element::Image:
			return new ImageState(tileset->image());
		case Element::TileOffset:
			return new TileOffsetState(&tileOffset);
		default:
			return BaseState::handleElement(element);
	}
}

void TilesetState::finish()
{
	tileset->setTileOffset(tileOffset);
}

TileOffsetState::TileOffsetState(QPoint* tileOffset) : tileOffset(tileOffset)
{
}

void TileOffsetState::handleAttribute(Attribute::Type attribute, const QString& value)
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

LayerState::LayerState(Layer* layer) : BaseState(layer), layer(layer)
{
}

void LayerState::handleAttribute(format::Attribute::Type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::Name:
			layer->setName(value);
			break;
		case Attribute::Width:
			layer->setWidth(value.toInt());
			break;
		case Attribute::Height:
			layer->setHeight(value.toInt());
			break;
		case Attribute::Opacity:
			layer->setOpacity(value.toFloat());
			break;
		case Attribute::Visible:
			layer->setVisible(value.toInt()!=0);
			break;
	}
}

TileLayerState::TileLayerState(TileLayer* tileLayer) : LayerState(tileLayer), tileLayer(tileLayer), data(nullptr)
{
}

void TileLayerState::handleAttribute(Attribute::Type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::X:
			tileLayer->setX(value.toInt());
			break;
		case Attribute::Y:
			tileLayer->setY(value.toInt());
			break;
		default:
			LayerState::handleAttribute(attribute, value);
	}
}

BuilderState* TileLayerState::handleElement(Element::Type element)
{
	switch (element)
	{
		case Element::Data: {
			data = new Data();
			return new DataState(data);
		}
		default:
			return LayerState::handleElement(element);
	}
}

void TileLayerState::finish()
{
	if (data) {
		tileLayer->setCellData(data);
		delete data;
	}
}

ImageLayerState::ImageLayerState(ImageLayer* imageLayer) : LayerState(imageLayer), imageLayer(imageLayer)
{
}

BuilderState* ImageLayerState::handleElement(format::Element::Type element)
{
	switch (element)
	{
		case Element::Image:
			return new ImageState(imageLayer->image());
		default:
			return LayerState::handleElement(element);
	}
}

ObjectLayerState::ObjectLayerState(ObjectLayer* objectLayer) : LayerState(objectLayer), objectLayer(objectLayer)
{
}

BuilderState* ObjectLayerState::handleElement(format::Element::Type element)
{
	return LayerState::handleElement(element);
//	switch (element)
//	{
//		default:
//			return BaseState::handleElement(element);
//	}
}

DataState::DataState(Data* data) : data(data)
{
}

void DataState::handleAttribute(Attribute::Type attribute, const QString& value)
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

void ImageState::handleAttribute(Attribute::Type attribute, const QString& value)
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
			image->setTransparentColor(("FF"+value).toUInt(nullptr, 16));
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

void Builder::createElement(const QString& elementName)
{
	_stateStack.push(currentState()->handleElement(Element::type(elementName)));
}

void Builder::finishElement(const QString& elementName)
{
	BuilderState* state = _stateStack.pop();
	state->finish();
	delete state;
}

void Builder::setAttribute(const QString& attributeName, const QString& value)
{
	currentState()->handleAttribute(Attribute::type(attributeName), value);
}

void Builder::setData(const QString& bytes)
{
	currentState()->handleData(bytes);
}
