#include <tmx/Data.h>

#include <zlib.h>

#include <QDebug>

using namespace tmx;

Data::Data()
: _encoding(NoEncoding)
, _compression(NoCompression)
{
}


const QByteArray& Data::bytes() const
{
	return _bytes;
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
			_bytes = uncompress(QByteArray::fromBase64(bytes));
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

QByteArray Data::uncompressGzip(const QByteArray& data)
{
	if (data.size() <= 4) {
		qWarning("gUncompress: Input data is truncated");
		return QByteArray();
	}

	QByteArray result;

	int ret;
	z_stream strm;
	static const int CHUNK_SIZE = 1024;
	char out[CHUNK_SIZE];

	/* allocate inflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = data.size();
	strm.next_in = (Bytef*)(data.data());

	ret = inflateInit2(&strm, 15 +  32); // gzip decoding
	if (ret != Z_OK)
		return QByteArray();

	// run inflate()
	do {
		strm.avail_out = CHUNK_SIZE;
		strm.next_out = (Bytef*)(out);

		ret = inflate(&strm, Z_NO_FLUSH);
		Q_ASSERT(ret != Z_STREAM_ERROR);  // state not clobbered

		switch (ret) {
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;     // and fall through
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);
			return QByteArray();
		}

		result.append(out, CHUNK_SIZE - strm.avail_out);
	} while (strm.avail_out == 0);

	// clean up and return
	inflateEnd(&strm);
	return result;
}
