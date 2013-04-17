#pragma once

#include <tmx/Base.h>
#include <tmx/Image.h>

#include <QSize>
#include <QPoint>
#include <QString>

namespace tmx {

class Tileset : public Base
{
public:
	Tileset();

	unsigned firstGid() const;
	const QString& name() const;
	const QString& source() const;
	int spacing() const;
	int margin() const;
	const QSize& tileSize() const;

	void setFirstGid(unsigned gid);
	void setSource(const QString& source);
	void setName(const QString& name);
	void setSpacing(int spacing);
	void setMargin(int margin);

	QPoint& tileOffset();
	Image& image();

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
};

} // namespace tmx
