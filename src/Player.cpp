#include <Player.h>

Player::Player()
{
	_margin = 2;
	_animation.setImage("data/spieler_by_samidare88-d6214g5.png");
	_animation.setSize(QSize(32,32));
	_animation.setDuration(1);
	_size = QSize(32,32);
}
