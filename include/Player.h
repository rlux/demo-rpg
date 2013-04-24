#pragma once

#include <AnimatedObject.h>

class Player : public AnimatedObject
{
public:
	Player();

	virtual bool isPlayer() const;
};
