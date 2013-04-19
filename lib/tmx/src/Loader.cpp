#include <tmx/Loader.h>

#include <tmx/XmlHandler.h>
#include <tmx/Builder.h>

#include <QtXml/QtXml>
#include <QFile>
#include <QDebug>

using namespace tmx;

Map* Loader::loadMap(const QString& filename)
{
	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "could not open file " << filename;
		return nullptr;
	}

	QXmlSimpleReader xmlReader;
	Builder builder;
	XmlHandler* handler = new XmlHandler(&builder);
	QXmlInputSource* source = new QXmlInputSource(&file);

	xmlReader.setContentHandler(handler);
	xmlReader.setErrorHandler(handler);

	bool ok = xmlReader.parse(source);

	Map* map = builder.map();
	map->setFilename(filename);

	delete handler;

	return map;
}
