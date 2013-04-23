#pragma once

#include <AnimatedObject.h>
#include <QString>

class NPC : public AnimatedObject
{
public:
	NPC();

	const QString& name() const;
	void setName(const QString& name);
protected:
	QString _name;
};
