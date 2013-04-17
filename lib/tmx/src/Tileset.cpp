#include <tmx/Tileset.h>

using namespace tmx;

Tileset::Tileset()
: _spacing(0)
, _margin(0)
{
}

void Tileset::setFirstGid(unsigned gid)
{
	_firstGid = gid;
}

void Tileset::setSource(const QString& source)
{
	_source = source;
}

void Tileset::setName(const QString& name)
{
	_name = name;
}

void Tileset::setSpacing(int spacing)
{
	_spacing = spacing;
}

void Tileset::setMargin(int margin)
{
	_margin = margin;
}

QPoint& Tileset::tileOffset()
{
	return _tileOffset;
}

QString Tileset::toString() const
{
	return QString("Tileset(%1 %2 %3 %4 %5 %6x%7)").arg(_name).arg(_firstGid).arg(_spacing).arg(_margin).arg(_source).arg(_tileOffset.x()).arg(_tileOffset.y());
}
