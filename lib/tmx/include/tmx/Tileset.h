#pragma once

#include <tmx/Base.h>
#include <tmx/Image.h>
#include <tmx/Tile.h>

#include <QSize>
#include <QPoint>
#include <QString>
#include <QHash>

namespace tmx {

class Tileset : public Base
{
public:
	Tileset();
	~Tileset();

	unsigned firstGid() const;
	const QString& name() const;
	const QString& source() const;
	int spacing() const;
	int margin() const;
	const QSize& tileSize() const;
	const QPoint& tileOffset() const;

	void setFirstGid(unsigned gid);
	void setSource(const QString& source);
	void setName(const QString& name);
	void setSpacing(int spacing);
	void setMargin(int margin);
	void setTileSize(const QSize& size);
	void setTileWidth(int width);
	void setTileHeight(int height);
	void setTileOffset(const QPoint& offset);

	Tile* atGid(unsigned gid);
	Tile* at(unsigned id);

	Image* image();

	QString toString() const;
protected:
	unsigned _firstGid;
	QString _source;
	QString _name;
	QSize _tileSize;
	int _spacing;
	int _margin;
	QPoint _tileOffset;
	Image _image;
	QHash<unsigned, Tile*> _tiles;
};

} // namespace tmx
