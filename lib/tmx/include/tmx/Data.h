#pragma once

#include <QString>
#include <QHash>

namespace tmx {

class Data
{
public:
	enum Encoding {
		NoEncoding,
		Base64,
		Csv
	};
	enum Compression {
		NoCompression,
		Zlib,
		Gzip
	};

	Data();

	const QByteArray& bytes() const;

	template<typename T> T at(unsigned index) const;

	void setEncoding(Encoding encoding);
	void setCompression(Compression compression);
	void setBytes(const QByteArray& bytes);

	static Encoding encodingFromString(const QString& string);
	static Compression compressionFromString(const QString& string);
protected:
	Encoding _encoding;
	Compression _compression;
	QByteArray _bytes;

	QByteArray uncompress(const QByteArray& bytes);

	static QByteArray uncompressZlib(const QByteArray& bytes);
	static QByteArray uncompressGzip(const QByteArray& bytes);
};

template<typename T>
T Data::at(unsigned index) const
{
	return ((T*)_bytes.data())[index];
}

} // namespace tmx
