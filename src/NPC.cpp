#include <NPC.h>

NPC::NPC()
{
	setDirection(Right);
}

bool NPC::isNPC() const
{
	return true;
}

const QString& NPC::name() const
{
	return _name;
}

void NPC::setName(const QString& name)
{
	_name = name;
}

void NPC::hitObstacle()
{
	unsigned i = 1+qrand()%4;
	setDirection(AnimatedObject::Direction(i));
}
