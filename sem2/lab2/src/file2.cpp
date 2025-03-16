#include "file2.hpp"

Base32File2::Base32File2(IFile *file) : file(file) {}

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
    return file->write(buf, n_bytes);
}

size_t Base32File2::read(void *buf, size_t max_bytes)
{
    return file->read(buf, max_bytes);
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
    return file->write(buf, n_bytes);
}

size_t RleFile2::read(void *buf, size_t max_bytes)
{
    return file->read(buf, max_bytes);
}
