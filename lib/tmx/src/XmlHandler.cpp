#include <tmx/XmlHandler.h>

#include <QtXml/QtXml>
#include <QFile>
#include <QDebug>

using namespace tmx;

XmlHandler::XmlHandler()
{
}

Map* XmlHandler::map() const
{
	return _builder.map();
}

bool XmlHandler::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attributes)
{
	QString tag = localName.toLower();
	_tags.push(tag);

	_builder.create(tag);

	setAttributes(attributes);

	return true;
}

void XmlHandler::setAttributes(const QXmlAttributes& attributes)
{
	for (int i=0; i< attributes.length(); ++i)
	{
		_builder.setAttribute(attributes.localName(i), attributes.value(i));
	}
}

bool XmlHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	QString tag = localName.toLower();
	_tags.pop();

	_builder.finish(tag);

	return true;
}

bool XmlHandler::characters(const QString& characters)
{
	//qDebug() << characters;

	return true;
}

