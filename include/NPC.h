#pragma once

#include <AnimatedObject.h>
#include <QString>

class NPC : public AnimatedObject
{
public:
	NPC();

	const QString& type() const;
	void setType(const QString& type);
protected:
	QString _type;
};
