#include <tmx/TileLayer.h>

using namespace tmx;

TileLayer::TileLayer()
: _visible(true)
, _opacity(1)
{
}

void TileLayer::setName(const QString& name)
{
	_name = name;
}

void TileLayer::setSize(const QSize& size)
{
	_size = size;
}

void TileLayer::setWidth(int width)
{
	_size.setWidth(width);
}

void TileLayer::setHeight(int height)
{
	_size.setHeight(height);
}

void TileLayer::setPosition(const QPoint& position)
{
	_position = position;
}

void TileLayer::setX(int x)
{
	_position.setX(x);
}

void TileLayer::setY(int y)
{
	_position.setY(y);
}

void TileLayer::setOpacity(float opacity)
{
	_opacity = opacity;
}

void TileLayer::setVisible(bool visible)
{
	_visible = visible;
}

Data& TileLayer::data()
{
	return _data;
}

int TileLayer::at(int x, int y) const
{
	return ((int*)_data.data().data())[y*_size.width()+x];
}
#include <QDebug>
QString TileLayer::toString() const
{
//	QString str;
//	for (int y=0;y<_size.height();++y) {
//		for (int x=0;x<_size.width();++x) {
//			str += QString::number(at(x,y))+",";
//		}
//		str+="\n";
//	}
//	qDebug() << str;
	return QString("TileLayer(%1 %2x%3)").arg(_name).arg(_size.width()).arg(_size.height());
}
