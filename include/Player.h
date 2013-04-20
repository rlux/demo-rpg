#pragma once

#include <QPoint>

class Player
{
public:
	void setPosition(const QPoint& position);
	const QPoint& position() const;
protected:
	QPoint _position;
};
