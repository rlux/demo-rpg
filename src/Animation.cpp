#include <Animation.h>

#include <cmath>

Animation::Animation()
: _direction(Down)
, _running(false)
, _duration(1)
, _currentStep(0)
, _pixmap(nullptr)
{
}

Animation::~Animation()
{
	delete _pixmap;
}

void Animation::setImage(const QString& filename)
{
	_pixmap = new QPixmap(filename);
}

void Animation::setSize(const QSize& size)
{
	_size = size;
}

void Animation::setDuration(double duration)
{
	_duration = duration;
}

void Animation::setSteps(const QList<unsigned>& steps)
{
	_steps = steps;
}

void Animation::setOffset(Direction direction, unsigned offset)
{
	_directionOffsets.insert(direction, offset);
}

void Animation::setRunning(bool running)
{
	_running = running;
}

void Animation::setDirection(Direction direction)
{
	_direction = direction;
}

void Animation::update(double delta)
{
	_current = fmod(_current + delta, _duration);
	_currentStep = (unsigned)(_steps.size()*_current/_duration);
}

void Animation::render(QPainter& painter, const QRectF& area)
{
	if (_pixmap)
	{
		painter.drawPixmap(area, *_pixmap, rect());
	}
}

QRect Animation::rect() const
{
	return QRect(QPoint((_running?_steps[_currentStep]:1)*_size.width(), _directionOffsets.value(_direction, 0)*_size.height()), _size);
}

