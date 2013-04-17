#include <tmx/Data.h>

#include <QDebug>

using namespace tmx;

Data::Data()
: _encoding(NoEncoding)
, _compression(NoCompression)
{
}


const QByteArray& Data::data() const
{
	return _data;
}

void Data::setEncoding(Encoding encoding)
{
	_encoding = encoding;
}

void Data::setCompression(Compression compression)
{
	_compression = compression;
}

Data::Encoding Data::encodingFromString(const QString& string)
{
	if (string=="base64") {
		return Base64;
	} else if (string=="csv") {
		return Csv;
	} else {
		return NoEncoding;
	}
}

Data::Compression Data::compressionFromString(const QString& string)
{
	if (string=="zlib") {
		return Zlib;
	} else if (string=="gzip") {
		return Gzip;
	} else {
		return NoCompression;
	}
}

void Data::setBytes(const QByteArray& bytes)
{
	switch (_encoding)
	{
		case Csv:
			qDebug() << "Csv encoding not supported yet";
			return;
		case Base64:
			_data = uncompress(QByteArray::fromBase64(bytes));
			break;
		default:
			qDebug() << "cannot set bytes without encoding";
			return;
	}
}

QByteArray Data::uncompress(const QByteArray& bytes)
{
	switch (_compression)
	{
		case Zlib:
			return uncompressZlib(bytes);
		case Gzip:
			return uncompressGzip(bytes);
		default:
			return bytes;
	}

}

QByteArray Data::uncompressZlib(const QByteArray& bytes)
{
	unsigned size = bytes.size();

	QByteArray dataPlusSize;

	//BigEndian order
	dataPlusSize.append((unsigned int)((size >> 24) & 0xFF));
	dataPlusSize.append((unsigned int)((size >> 16) & 0xFF));
	dataPlusSize.append((unsigned int)((size >> 8) & 0xFF));
	dataPlusSize.append((unsigned int)((size >> 0) & 0xFF));
	dataPlusSize.append(bytes, bytes.size());

	return qUncompress(dataPlusSize);
}

QByteArray Data::uncompressGzip(const QByteArray& bytes)
{
	return qUncompress(bytes);
}
