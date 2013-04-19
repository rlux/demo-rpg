#pragma once

#include <tmx/Base.h>

#include <QPoint>
#include <QSize>
#include <QString>

namespace tmx {

class Object : public Base
{
public:
	Object();

	void setName(const QString& name);
	const QString& name() const;

	void setType(const QString& type);
	const QString& type() const;

	void setSize(const QSize& size);
	const QSize& size() const;
	void setWidth(int width);
	int width() const;
	void setHeight(int height);
	int height() const;

	void setPosition(const QPoint& position);
	void setX(int x);
	void setY(int y);

	void setVisible(bool visible);
	bool isVisible() const;

	void setGid(unsigned gid);
	unsigned gid() const;
protected:
	QString _name;
	QString _type;
	QPoint _position;
	QSize _size;
	bool _visible;
	unsigned _gid;
};

} // namespace tmx
