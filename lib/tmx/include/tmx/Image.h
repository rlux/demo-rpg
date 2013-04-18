#pragma once

#include <QString>
#include <QSize>
#include <QColor>

namespace tmx {

class Image
{
public:
	void setFormat(const QString& format);
	void setSource(const QString& source);
	void setTransparentColor(const QColor& color);
	void setSize(const QSize& size);
	void setWidth(int width);
	void setHeight(int height);

	const QString& format() const;
	const QString& source() const;
	const QSize& size() const;
	int width() const;
	int height() const;
protected:
	QString _format;
	QString _source;
	QColor _transparentColor;
	QSize _size;
};

} // namespace tmx
