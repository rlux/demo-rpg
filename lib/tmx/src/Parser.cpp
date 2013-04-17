#include <tmx/Parser.h>

#include <tmx/XmlHandler.h>

#include <QtXml/QtXml>
#include <QFile>
#include <QDebug>

using namespace tmx;

void Parser::parseFile(const QString& filename)
{
	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "could not open file " << filename;
		return;
	}

	QXmlSimpleReader xmlReader;
	XmlHandler* handler = new XmlHandler();
	QXmlInputSource* source = new QXmlInputSource(&file);

	xmlReader.setContentHandler(handler);
	xmlReader.setErrorHandler(handler);

	bool ok = xmlReader.parse(source);

	//qDebug() << (ok?"ok":"not ok");
	qDebug() << handler->map()->toString();

	delete handler;
}
