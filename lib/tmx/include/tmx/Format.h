#pragma once

#include <QString>
#include <QHash>

namespace tmx {

class Format
{
public:
	enum Element {
		UnknownElement,
		Map,
		Tileset,
		Layer,
		Tile,
		Image,
		ObjectGroup,
		Object,
		Data,
		TileOffset
	};
	enum Attribute {
		UnknownAttribute,
		Id,
		Gid,
		FirstGid,
		Name,
		Orientation,
		Width,
		Height,
		X,
		Y,
		TileWidth,
		TileHeight,
		Encoding,
		Compression,
		Version,
		Spacing,
		Margin,
		Visible,
		Opacity,
		ImageFormat,
		Source,
		Trans
	};

	static Element element(const QString& name);
	static Attribute attribute(const QString& name);
protected:
	static QHash<QString, Element> _elementMap;
	static QHash<QString, Attribute> _attributeMap;

	static QHash<QString, Element> createElementMap();
	static QHash<QString, Attribute> createAttributeMap();
private:
	Format();
};

} // namespace tmx
