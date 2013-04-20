#include <tmx/Format.h>

using namespace tmx::format;

namespace {

QHash<QString, Element::type> createElementMap()
{
	QHash<QString, Element::type> elementMap;

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
	elementMap.insert("property", Element::Property);
	elementMap.insert("terraintypes", Element::TerrainTypes);
	elementMap.insert("terrain", Element::Terrain);
	elementMap.insert("ellipse", Element::Ellipse);
	elementMap.insert("polygon", Element::Polygon);
	elementMap.insert("polyline", Element::Polyline);

	return elementMap;
}

QHash<QString, Attribute::type> createAttributeMap()
{
	QHash<QString, Attribute::type> attributeMap;

	attributeMap.insert("id", Attribute::Id);
	attributeMap.insert("gid", Attribute::Gid);
	attributeMap.insert("firstgid", Attribute::FirstGid);
	attributeMap.insert("name", Attribute::Name);
	attributeMap.insert("value", Attribute::Value);
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
	attributeMap.insert("tile", Attribute::Tile);
	attributeMap.insert("color", Attribute::Color);
	attributeMap.insert("type", Attribute::Type);
	attributeMap.insert("points", Attribute::Points);

	return attributeMap;
}

}

QHash<QString, Element::type> Element::typeMap = createElementMap();
QHash<QString, Attribute::type> Attribute::typeMap = createAttributeMap();


Element::type Element::fromString(const QString& name)
{
	return typeMap.value(name, Unknown);
}

Attribute::type Attribute::fromString(const QString& name)
{
	return typeMap.value(name, Unknown);
}

