#include <tmx/XmlHandler.h>

#include <QtXml/QtXml>
#include <QFile>
#include <QDebug>

using namespace tmx;

XmlHandler::XmlHandler(Builder* builder)
: _builder(builder)
{
}

bool XmlHandler::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attributes)
{
	_builder->createElement(localName.toLower());

	setAttributes(attributes);

	return true;
}

void XmlHandler::setAttributes(const QXmlAttributes& attributes)
{
	for (int i=0; i< attributes.length(); ++i)
	{
		_builder->setAttribute(attributes.localName(i), attributes.value(i));
	}
}

bool XmlHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	_builder->finishElement(localName.toLower());

	return true;
}

bool XmlHandler::characters(const QString& characters)
{
	_builder->setData(characters.trimmed());

	return true;
}

