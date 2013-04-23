#include <Player.h>

Player::Player()
{
	setSize(QSize(32,32));
	setMargins(QMargins(5, 12, -5, 0));

	_animation.setImage("data/spieler_by_samidare88-d6214g5.png");
	_animation.setSize(QSize(32,32));
	_animation.setDuration(0.5);
	_animation.setSteps(QList<unsigned>() << 0 << 1 << 2 << 1);
}
