#include "file2.hpp"
#include "coder.hpp"

Base32File2::Base32File2(IFile *file, const char *table) : file(file), table(table) {}

Base32File2::~Base32File2()
{
    delete file;
}

bool Base32File2::can_read() const
{
    return file->can_read();
}

bool Base32File2::can_write() const
{
    return file->can_write();
}

size_t Base32File2::write(const void *buf, size_t n_bytes)
{
    size_t size = _encoded32_size(n_bytes);
    char *encodedData = new char[size];
    if (_encode32(static_cast<const char *>(buf), n_bytes, encodedData, table) != 0)
    {
        delete[] encodedData;
        throw std::runtime_error("Failed to encode data");
    }

    size_t result = file->write(encodedData, size);
    delete[] encodedData;
    return result;
}

size_t Base32File2::read(void *buf, size_t max_bytes)
{
    size_t encodedSize = _encoded32_size(max_bytes);
    char *encodedData = new char[encodedSize];
    size_t readSize = file->read(encodedData, encodedSize);

    char *decodedData = static_cast<char *>(buf);
    if (_decode32(encodedData, readSize, decodedData, table) != 0)
    {
        delete[] encodedData;
        throw std::runtime_error("Failed to decode data in b32");
    }

    delete[] encodedData;
    return _decoded32_size(readSize);
}

// RLE FILE

RleFile2::RleFile2(IFile *file) : file(file) {}

RleFile2::~RleFile2()
{
    delete file;
}

bool RleFile2::can_read() const
{
    return file->can_read();
}

bool RleFile2::can_write() const
{
    return file->can_write();
}

size_t RleFile2::write(const void *buf, size_t n_bytes)
{
    size_t output_size;
    const char *encodedData = _encodeRLE(static_cast<const char *>(buf), n_bytes, output_size);

    size_t result = file->write(encodedData, output_size);

    delete[] encodedData;
    return result;
}

size_t RleFile2::read(void *buf, size_t max_bytes)
{
    size_t readSize = file->read(buf, max_bytes);

    char *decodedData = static_cast<char *>(buf);
    if (_decodeRLE(static_cast<const char *>(buf), readSize, decodedData) != 0)
    {
        throw std::runtime_error("Failed to decode data in rle");
    }

    return readSize;
}
