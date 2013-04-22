#include <Animation.h>

Animation::Animation()
: _direction(Right)
, _running(true)
, _duration(1)
{
}

void Animation::setImage(const QString& filename)
{
	_pixmap = QPixmap(filename);
}

void Animation::setSize(const QSize& size)
{
	_size = size;
}

void Animation::setDuration(double duration)
{
	_duration = duration;
}

void Animation::render(QPainter& painter, const QRectF& area)
{
	painter.drawPixmap(area, _pixmap, rect());
}

QRect Animation::rect() const
{
	return QRect(QPoint(), _size);
}
