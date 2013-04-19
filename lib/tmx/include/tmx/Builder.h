#pragma once

#include <tmx/Format.h>
#include <tmx/Map.h>
#include <tmx/Tileset.h>
#include <tmx/TileLayer.h>
#include <tmx/ImageLayer.h>
#include <tmx/Data.h>
#include <tmx/Object.h>

#include <QHash>
#include <QStack>
#include <QList>

namespace tmx {

class BuilderState
{
public:
	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
	virtual void handleData(const QString& data);
	virtual BuilderState* handleElement(format::Element::type element);
	virtual void finish();
};

class StartState : public BuilderState
{
public:
	virtual BuilderState* handleElement(format::Element::type element);

	QList<Map*> maps;
};

class BaseState : public BuilderState
{
public:
	BaseState(Base* base);

	virtual BuilderState* handleElement(format::Element::type element);
protected:
	Base* base;
};

class PropertiesState : public BuilderState
{
public:
	PropertiesState(Base* base);

	virtual BuilderState* handleElement(format::Element::type element);
protected:
	Base* base;
};

class PropertyState : public BuilderState
{
public:
	PropertyState(Base* base);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
	virtual void finish();
protected:
	Base* base;
	QString propertyName;
	QString propertyValue;
};

class MapState : public BaseState
{
public:
	MapState(Map* map);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
	virtual BuilderState* handleElement(format::Element::type element);
protected:
	Map* map;
};

class TilesetState : public BaseState
{
public:
	TilesetState(Tileset* tileset);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
	virtual BuilderState* handleElement(format::Element::type element);
	virtual void finish();
protected:
	Tileset* tileset;
	QPoint tileOffset;
};

class TileOffsetState : public BuilderState
{
public:
	TileOffsetState(QPoint* tileOffset);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
protected:
	QPoint* tileOffset;
};

class TerraintypesState : public BuilderState
{
public:
	TerraintypesState(Tileset* tileset);

	virtual BuilderState* handleElement(format::Element::type element);
protected:
	Tileset* tileset;
};

class TerrainState : public BuilderState
{
public:
	TerrainState(Tileset* tileset);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
	virtual BuilderState* handleElement(format::Element::type element);
	virtual void finish();
protected:
	Tileset* tileset;
	unsigned tileId;
	QString name;
};

class LayerState : public BaseState
{
public:
	LayerState(Layer* layer);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
protected:
	Layer* layer;
};

class TileLayerState : public LayerState
{
public:
	TileLayerState(TileLayer* tileLayer);

	virtual BuilderState* handleElement(format::Element::type element);
	virtual void finish();
protected:
	TileLayer* tileLayer;
	Data* data;
};

class ImageLayerState : public LayerState
{
public:
	ImageLayerState(ImageLayer* imageLayer);

	virtual BuilderState* handleElement(format::Element::type element);
protected:
	ImageLayer* imageLayer;
};

class ObjectLayerState : public LayerState
{
public:
	ObjectLayerState(ObjectLayer* objectLayer);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
	virtual BuilderState* handleElement(format::Element::type element);
protected:
	ObjectLayer* objectLayer;
};

class ObjectState : public BaseState
{
public:
	ObjectState(Object* object);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
protected:
	Object* object;
};

class DataState : public BuilderState
{
public:
	DataState(Data* data);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
	virtual void handleData(const QString& data);
protected:
	Data* data;
};

class ImageState : public BuilderState
{
public:
	ImageState(Image* image);

	virtual void handleAttribute(format::Attribute::type attribute, const QString& value);
protected:
	Image* image;
};


class Builder
{
public:
	Builder();
	~Builder();

	void createElement(const QString& elementName);
	void finishElement(const QString& elementName);
	void setAttribute(const QString& attributeName, const QString& value);
	void setData(const QString& bytes);

	Map* map() const;
protected:
	StartState* _startState;
	QStack<BuilderState*> _stateStack;

	BuilderState* currentState();
};


} // namespace tmx
