#pragma once

#include <QString>
#include <QHash>

namespace tmx {
namespace format {

class Element
{
public:
	enum type {
		Unknown,
		Map,
		Tileset,
		Layer,
		ImageLayer,
		Tile,
		Image,
		ObjectGroup,
		Object,
		Data,
		TileOffset,
		Properties,
		Property,
		TerrainTypes,
		Terrain,
		Ellipse,
		Polygon,
		Polyline
	};

	static type fromString(const QString& name);
protected:
	static QHash<QString, type> typeMap;
};

class Attribute
{
public:
	enum type {
		Unknown,
		Id,
		Gid,
		FirstGid,
		Name,
		Value,
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
		Format,
		Source,
		Trans,
		BackgroundColor,
		Tile,
		Color,
		Type,
		Points
	};

	static type fromString(const QString& name);
protected:
	static QHash<QString, type> typeMap;
};

} // namespace format
} // namespace tmx
