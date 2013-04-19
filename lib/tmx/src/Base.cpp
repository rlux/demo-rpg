#include <tmx/Base.h>

using namespace tmx;

void Base::setProperty(const QString& property, const QString& value)
{
	_properties.insert(property, value);
}

QString Base::property(const QString& property) const
{
	return _properties.value(property, QString());
}
