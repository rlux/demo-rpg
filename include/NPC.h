#pragma once

#include <AnimatedObject.h>
#include <QString>

class NPC : public AnimatedObject
{
public:
	NPC();

	virtual bool isNPC() const;

	const QString& name() const;
	void setName(const QString& name);

	virtual void hitObstacle();
protected:
	QString _name;
};
