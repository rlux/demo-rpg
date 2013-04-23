#pragma once

#include <NPC.h>
#include <QString>
#include <QHash>

class NPCFactory
{
public:
	NPCFactory();
	~NPCFactory();

	NPC* createNpc(const QString& name) const;
	NPC* createNpc(const QString& name, const QPointF& position) const;

	void addPrototype(const QString& name, NPC* prototype);
protected:
	QHash<QString, NPC*> _prototypes;
};
