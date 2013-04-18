#include <tmx/Parser.h>

#include <tmx/XmlHandler.h>
#include <tmx/Builder.h>

#include <QtXml/QtXml>
#include <QFile>
#include <QDebug>

using namespace tmx;

Parser::Parser()
: _map(nullptr)
{
}

Map* Parser::map()
{
	return _map;
}

void Parser::parseFile(const QString& filename)
{
	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "could not open file " << filename;
		return;
	}

	QXmlSimpleReader xmlReader;
	Builder builder;
	XmlHandler* handler = new XmlHandler(&builder);
	QXmlInputSource* source = new QXmlInputSource(&file);

	xmlReader.setContentHandler(handler);
	xmlReader.setErrorHandler(handler);

	bool ok = xmlReader.parse(source);

	_map = builder.map();
	_map->setFilename(filename);

	delete handler;
}
