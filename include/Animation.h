#pragma once

#include <QPixmap>
#include <QSize>
#include <QRectF>
#include <QPainter>
#include <QList>
#include <QMap>

class Animation
{
public:
	enum Direction {
		Left,
		Right,
		Up,
		Down
	};

	Animation();
	~Animation();

	void setImage(const QString& filename);

	void setSize(const QSize& size);
	void setDuration(double duration);
	void setSteps(const QList<unsigned>& steps);
	void setRunning(bool running);
	void setDirection(Direction direction);
	void setOffset(Direction direction, unsigned offset);

	void update(double delta);

	QPixmap* pixmap();
	QRect rect() const;
protected:
	Direction _direction;
	double _duration;
	double _current;
	unsigned _currentStep;
	QSize _size;
	QList<unsigned> _steps;
	QPixmap* _pixmap;
	bool _running;
	QMap<Direction, unsigned> _directionOffsets;
};
