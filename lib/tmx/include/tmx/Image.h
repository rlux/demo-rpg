#pragma once

#include <QString>
#include <QSize>

namespace tmx {

class Image
{
public:
	void setFormat(const QString& format);
	void setSource(const QString& source);
	void setTrans(const QString& trans);
	void setSize(const QSize& size);
	void setWidth(int width);
	void setHeight(int height);

	QString source() const;
protected:
	QString _format;
	QString _source;
	QString _trans;
	QSize _size;
};

} // namespace tmx
