#include <Animation.h>

#include <cmath>

Animation::Animation()
: _direction(Down)
, _running(false)
, _duration(1)
, _steps(3)
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

void Animation::setSteps(unsigned steps)
{
	_steps = steps;
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
	_currentStep = (unsigned)(_steps*_current/_duration);
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
	return QRect(QPoint((_running?_currentStep:1)*_size.width(), indexOf(_direction)*_size.height()), _size);
}

unsigned Animation::indexOf(Direction direction) const
{
	switch (direction)
	{
		case Down:
			return 0;
		case Left:
			return 1;
		case Right:
			return 2;
		case Up:
			return 3;
		default:
			return 0;
	}
}

