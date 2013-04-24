#pragma once

#include <QString>
#include <QHash>

namespace tmx {

class Base
{
public:
	void setProperty(const QString& property, const QString& value);
	QString property(const QString& property) const;

	const QHash<QString, QString>& properties() const;
protected:
	QHash<QString, QString> _properties;
};

} // namespace tmx
