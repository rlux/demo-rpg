#include <NPC.h>

NPC::NPC()
{
}

const QString& NPC::name() const
{
	return _name;
}

void NPC::setName(const QString& name)
{
	_name = name;
}
