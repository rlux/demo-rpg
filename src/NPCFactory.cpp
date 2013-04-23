#include <NPCFactory.h>

NPCFactory::NPCFactory()
{
}

NPCFactory::~NPCFactory()
{
	qDeleteAll(_prototypes);
}

NPC* NPCFactory::createNpc(const QString& name) const
{
	NPC* prototype = _prototypes.value(name, nullptr);
	if (!prototype) return new NPC();
	return new NPC(*prototype);
}

NPC* NPCFactory::createNpc(const QString& name, const QPointF& position) const
{
	NPC* npc = createNpc(name);
	npc->setPosition(position);
	return npc;
}

void NPCFactory::addPrototype(const QString& name, NPC* prototype)
{
	_prototypes.insert(name, prototype);
}
