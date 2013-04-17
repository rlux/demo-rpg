#pragma once

#include <tmx/Format.h>
#include <tmx/Map.h>
#include <tmx/Tileset.h>
#include <tmx/TileLayer.h>
#include <tmx/ImageLayer.h>

#include <QHash>
#include <QStack>
#include <QList>

namespace tmx {

class BuilderState
{
public:
	virtual void setAttribute(format::Attribute::Type attribute, const QString& value);
	virtual void handleData(const QString& data);
	virtual BuilderState* handleElement(format::Element::Type element);
};

class DefaultState : public BuilderState
{
public:
	virtual BuilderState* handleElement(format::Element::Type element);
};

class StartState : public BuilderState
{
public:
	virtual BuilderState* handleElement(format::Element::Type element);

	QList<Map*> maps;
};

class MapState : public DefaultState
{
public:
	MapState(Map* map);

	virtual void setAttribute(format::Attribute::Type attribute, const QString& value);
	virtual BuilderState* handleElement(format::Element::Type element);
protected:
	Map* map;
};

class TilesetState : public DefaultState
{
public:
	TilesetState(Tileset* tileset);

	virtual void setAttribute(format::Attribute::Type attribute, const QString& value);
	virtual BuilderState* handleElement(format::Element::Type element);
protected:
	Tileset* tileset;
};

class TileOffsetState : public BuilderState
{
public:
	TileOffsetState(QPoint* tileOffset);

	virtual void setAttribute(format::Attribute::Type attribute, const QString& value);
protected:
	QPoint* tileOffset;
};

class TileLayerState : public DefaultState
{
public:
	TileLayerState(TileLayer* tileLayer);

	virtual void setAttribute(format::Attribute::Type attribute, const QString& value);
	virtual BuilderState* handleElement(format::Element::Type element);
protected:
	TileLayer* tileLayer;
};

class ImageLayerState : public DefaultState
{
public:
	ImageLayerState(ImageLayer* imageLayer);

	virtual BuilderState* handleElement(format::Element::Type element);
protected:
	ImageLayer* imageLayer;
};

class ObjectLayerState : public DefaultState
{
public:
	ObjectLayerState(ObjectLayer* objectLayer);

	virtual BuilderState* handleElement(format::Element::Type element);
protected:
	ObjectLayer* objectLayer;
};

class DataState : public BuilderState
{
public:
	DataState(Data* data);

	virtual void setAttribute(format::Attribute::Type attribute, const QString& value);
		virtual void handleData(const QString& data);
protected:
	Data* data;
};

class ImageState : public BuilderState
{
public:
	ImageState(Image* image);

	virtual void setAttribute(format::Attribute::Type attribute, const QString& value);
protected:
	Image* image;
};


class Builder
{
public:
	Builder();
	~Builder();

	void create(const QString& elementName);
	void finish(const QString& elementName);
	void setAttribute(const QString& attributeName, const QString& value);
	void data(const QString& bytes);

	Map* map() const;
protected:
	StartState* _startState;
	QStack<BuilderState*> _stateStack;

	BuilderState* currentState();
};


} // namespace tmx
