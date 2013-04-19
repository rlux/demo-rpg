#include <tmx/Format.h>

using namespace tmx::format;

namespace {

QHash<QString, Element::Type> createElementMap()
{
	QHash<QString, Element::Type> elementMap;

	elementMap.insert("map", Element::Map);
	elementMap.insert("tileset", Element::Tileset);
	elementMap.insert("tile", Element::Tile);
	elementMap.insert("image", Element::Image);
	elementMap.insert("layer", Element::Layer);
	elementMap.insert("imagelayer", Element::ImageLayer);
	elementMap.insert("object", Element::Object);
	elementMap.insert("objectgroup", Element::ObjectGroup);
	elementMap.insert("data", Element::Data);
	elementMap.insert("tileoffset", Element::TileOffset);
	elementMap.insert("properties", Element::Properties);

	return elementMap;
}

QHash<QString, Attribute::Type> createAttributeMap()
{
	QHash<QString, Attribute::Type> attributeMap;

	attributeMap.insert("id", Attribute::Id);
	attributeMap.insert("gid", Attribute::Gid);
	attributeMap.insert("firstgid", Attribute::FirstGid);
	attributeMap.insert("name", Attribute::Name);
	attributeMap.insert("orientation", Attribute::Orientation);
	attributeMap.insert("width", Attribute::Width);
	attributeMap.insert("height", Attribute::Height);
	attributeMap.insert("x", Attribute::X);
	attributeMap.insert("y", Attribute::Y);
	attributeMap.insert("tilewidth", Attribute::TileWidth);
	attributeMap.insert("tileheight", Attribute::TileHeight);
	attributeMap.insert("encoding", Attribute::Encoding);
	attributeMap.insert("compression", Attribute::Compression);
	attributeMap.insert("version", Attribute::Version);
	attributeMap.insert("spacing", Attribute::Spacing);
	attributeMap.insert("margin", Attribute::Margin);
	attributeMap.insert("opacity", Attribute::Opacity);
	attributeMap.insert("visible", Attribute::Visible);
	attributeMap.insert("format", Attribute::Format);
	attributeMap.insert("source", Attribute::Source);
	attributeMap.insert("trans", Attribute::Trans);
	attributeMap.insert("backgroundcolor", Attribute::BackgroundColor);

	return attributeMap;
}

}

QHash<QString, Element::Type> Element::typeMap = createElementMap();
QHash<QString, Attribute::Type> Attribute::typeMap = createAttributeMap();


Element::Type Element::type(const QString& name)
{
	return typeMap.value(name, Unknown);
}

Attribute::Type Attribute::type(const QString& name)
{
	return typeMap.value(name, Unknown);
}

