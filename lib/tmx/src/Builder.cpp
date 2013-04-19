#include <tmx/Builder.h>

#include <QDebug>

using namespace tmx;
using namespace tmx::format;


void BuilderState::handleAttribute(Attribute::type attribute, const QString& value)
{
}

void BuilderState::handleData(const QString& data)
{
}

BuilderState* BuilderState::handleElement(Element::type element)
{
	return new BuilderState();
}

void BuilderState::finish()
{
}

BuilderState* StartState::handleElement(Element::type element)
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

BuilderState* BaseState::handleElement(Element::type element)
{
	if (element == Element::Properties) {
		return new PropertiesState(base);
	} else {
		return BuilderState::handleElement(element);
	}
}

PropertiesState::PropertiesState(Base* base) : base(base)
{
}

BuilderState* PropertiesState::handleElement(format::Element::type element)
{
	if (element == Element::Property) {
		return new PropertyState(base);
	} else {
		return BuilderState::handleElement(element);
	}
}

PropertyState::PropertyState(Base* base) : base(base)
{
}

void PropertyState::handleAttribute(format::Attribute::type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::Name:
			propertyName = value;
			break;
		case Attribute::Value:
			propertyValue = value;
			break;
	}
}

 void PropertyState::finish()
 {
 	base->setProperty(propertyName, propertyValue);
 }

MapState::MapState(Map* map) : BaseState(map), map(map)
{
}

void MapState::handleAttribute(Attribute::type attribute, const QString& value)
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

BuilderState* MapState::handleElement(Element::type element)
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

void TilesetState::handleAttribute(Attribute::type attribute, const QString& value)
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

BuilderState* TilesetState::handleElement(Element::type element)
{
	switch (element)
	{
		case Element::Image:
			return new ImageState(tileset->image());
		case Element::TileOffset:
			return new TileOffsetState(&tileOffset);
		case Element::TerrainTypes:
			return new TerraintypesState(tileset);
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

void TileOffsetState::handleAttribute(Attribute::type attribute, const QString& value)
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

TerraintypesState::TerraintypesState(Tileset* tileset) : tileset(tileset)
{
}

BuilderState* TerraintypesState::handleElement(format::Element::type element)
{
	if (element==Element::Terrain) {
		return new TerrainState(tileset);
	} else {
		return new BuilderState();
	}
}

TerrainState::TerrainState(Tileset* tileset) : tileset(tileset), tileId(0)
{
}

void TerrainState::handleAttribute(format::Attribute::type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::Name:
			name = value;
			break;
		case Attribute::Tile:
			tileId = value.toUInt();
			break;
	}
}

BuilderState* TerrainState::handleElement(format::Element::type element)
{
	if (element==Element::Properties)
	{
		Tile* tile = tileset->at(tileId);
		if (tile)
		{
			return new PropertiesState(tile);
		}
	}

	return BuilderState::handleElement(element);
}

void TerrainState::finish()
{
	Tile* tile = tileset->at(tileId);
	if (tile)
	{
		tile->setName(name);
	}
}

LayerState::LayerState(Layer* layer) : BaseState(layer), layer(layer)
{
}

void LayerState::handleAttribute(format::Attribute::type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::Name:
			layer->setName(value);
			break;
		case Attribute::X:
			layer->setX(value.toInt());
			break;
		case Attribute::Y:
			layer->setY(value.toInt());
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

BuilderState* TileLayerState::handleElement(Element::type element)
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

BuilderState* ImageLayerState::handleElement(format::Element::type element)
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

void ObjectLayerState::handleAttribute(format::Attribute::type attribute, const QString& value)
{
	if (attribute == Attribute::Color)
	{
		//imageLayer->setColor();
	}
}

BuilderState* ObjectLayerState::handleElement(format::Element::type element)
{
	switch (element)
	{
		case Element::Object: {
			Object* object = new Object();
			objectLayer->addObject(object);
			return new ObjectState(object);
		}
		default:
			return LayerState::handleElement(element);
	}
}

ObjectState::ObjectState(Object* object) : BaseState(object), object(object)
{
}

void ObjectState::handleAttribute(format::Attribute::type attribute, const QString& value)
{
	switch (attribute)
	{
		case Attribute::Name:
			object->setName(value);
			break;
		case Attribute::Type:
			object->setType(value);
			break;
		case Attribute::Width:
			object->setWidth(value.toUInt());
			break;
		case Attribute::Height:
			object->setHeight(value.toUInt());
			break;
		case Attribute::X:
			object->setX(value.toUInt());
			break;
		case Attribute::Y:
			object->setY(value.toUInt());
			break;
		case Attribute::Gid:
			object->setGid(value.toUInt());
			break;
		case Attribute::Visible:
			object->setVisible(value.toUInt()!=0);
			break;
	}
}

DataState::DataState(Data* data) : data(data)
{
}

void DataState::handleAttribute(Attribute::type attribute, const QString& value)
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

void ImageState::handleAttribute(Attribute::type attribute, const QString& value)
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
	_stateStack.push(currentState()->handleElement(Element::fromString(elementName)));
}

void Builder::finishElement(const QString& elementName)
{
	BuilderState* state = _stateStack.pop();
	state->finish();
	delete state;
}

void Builder::setAttribute(const QString& attributeName, const QString& value)
{
	currentState()->handleAttribute(Attribute::fromString(attributeName), value);
}

void Builder::setData(const QString& bytes)
{
	currentState()->handleData(bytes);
}
