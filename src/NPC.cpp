#include <NPC.h>

NPC::NPC()
{
}

const QString& NPC::type() const
{
	return _type;
}

void NPC::setType(const QString& type)
{
	_type = type;
}
