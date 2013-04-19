#pragma once

#include <tmx/Base.h>

#include <QRect>

namespace tmx {

class Tileset;

class Tile : public Base
{
public:
	Tile();
	Tile(unsigned index, Tileset* tileset);

	Tileset* tileset() const;
	void setTileset(Tileset* tileset);

	unsigned index() const;
	void setIndex(unsigned index);

	QRect rect() const;

	void setName(const QString& name);
	const QString& name() const;
protected:
	Tileset* _tileset;
	unsigned _index;
	QRect _rect;
	QString _name;

	void updateRect();
};

} // namespace tmx
