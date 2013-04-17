#include <tmx/Format.h>

using namespace tmx;

QHash<QString, Format::Element> Format::_elementMap = createElementMap();
QHash<QString, Format::Attribute> Format::_attributeMap = createAttributeMap();

Format::Element Format::element(const QString& name)
{
	return _elementMap.value(name, UnknownElement);
}

Format::Attribute Format::attribute(const QString& name)
{
	return _attributeMap.value(name, UnknownAttribute);
}

QHash<QString, Format::Element> Format::createElementMap()
{
	QHash<QString, Element> elementMap;

	elementMap.insert("map", Map);
	elementMap.insert("tileset", Tileset);
	elementMap.insert("tile", Tile);
	elementMap.insert("image", Image);
	elementMap.insert("layer", Layer);
	elementMap.insert("object", Object);
	elementMap.insert("objectgroup", ObjectGroup);
	elementMap.insert("data", Data);
	elementMap.insert("tileoffset", TileOffset);

	return elementMap;
}

QHash<QString, Format::Attribute> Format::createAttributeMap()
{
	QHash<QString, Attribute> attributeMap;

	attributeMap.insert("id", Id);
	attributeMap.insert("gid", Gid);
	attributeMap.insert("firstgid", FirstGid);
	attributeMap.insert("name", Name);
	attributeMap.insert("orientation", Orientation);
	attributeMap.insert("width", Width);
	attributeMap.insert("height", Height);
	attributeMap.insert("x", X);
	attributeMap.insert("y", Y);
	attributeMap.insert("tilewidth", TileWidth);
	attributeMap.insert("tileheight", TileHeight);
	attributeMap.insert("encoding", Encoding);
	attributeMap.insert("compression", Compression);
	attributeMap.insert("version", Version);
	attributeMap.insert("spacing", Spacing);
	attributeMap.insert("margin", Margin);
	attributeMap.insert("opacity", Opacity);
	attributeMap.insert("visible", Visible);
	attributeMap.insert("format", ImageFormat);
	attributeMap.insert("source", Source);
	attributeMap.insert("trans", Trans);

	return attributeMap;
}
