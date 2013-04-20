#include <Player.h>


void Player::setPosition(const QPoint& position)
{
	_position = position;
}

const QPoint& Player::position() const
{
	return _position;
}
