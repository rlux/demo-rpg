#include <tmx/Image.h>

#include <QDebug>

using namespace tmx;

void Image::setFormat(const QString& format)
{
	_format = format;
}

void Image::setSource(const QString& source)
{
	_source = source;
	qDebug() << source;
}

QString Image::source() const
{
	return _source;
}

void Image::setTrans(const QString& trans)
{
	_trans = trans;
}

void Image::setSize(const QSize& size)
{
	_size = size;
}

void Image::setWidth(int width)
{
	_size.setWidth(width);
}

void Image::setHeight(int height)
{
	_size.setHeight(height);
}
