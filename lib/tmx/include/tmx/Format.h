#pragma once

#include <QString>
#include <QHash>

namespace tmx {
namespace format {

class Element
{
public:
	enum Type {
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
		Terrain
	};

	static Type type(const QString& name);
protected:
	static QHash<QString, Type> typeMap;
};

class Attribute
{
public:
	enum Type {
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
		Tile
	};

	static Type type(const QString& name);
protected:
	static QHash<QString, Type> typeMap;
};

} // namespace format
} // namespace tmx
