#include <tmx/Image.h>

using namespace tmx;

void Image::setFormat(const QString& format)
{
	_format = format;
}

void Image::setSource(const QString& source)
{
	_source = source;
}

const QString& Image::source() const
{
	return _source;
}

void Image::setTransparentColor(const QColor& color)
{
	_transparentColor = color;
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

const QSize& Image::size() const
{
	return _size;
}

int Image::width() const
{
	return _size.width();
}

int Image::height() const
{
	return _size.height();
}
