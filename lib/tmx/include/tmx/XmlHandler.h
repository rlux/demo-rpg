#pragma once

#include <tmx/Builder.h>

#include <QtXml/QXmlDefaultHandler>
#include <QString>

namespace tmx {

class XmlHandler : public QXmlDefaultHandler
{
public:
	XmlHandler();

	Map* map() const;

	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attributes);
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);
	virtual bool characters(const QString& characters);
protected:
	Builder _builder;

	void setAttributes(const QXmlAttributes& attributes);
};

} // namespace tmx
