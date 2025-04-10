#include "file.hpp"
#include "colors.hpp"

using std::cout;
using std::endl;

BaseFile::BaseFile() : file(nullptr)
{
    std::cout << BLUE << "BaseFile default constructor called for object: " << this
              << RESET << std::endl;
}

BaseFile::BaseFile(const char *path, const char *mode)
{
    file = fopen(path, mode);
    if (!file)
    {
        throw std::runtime_error("Error in constructor. Failed to open file");
    }
    std::cout << BLUE
              << "BaseFile parameterized constructor (with path and mode) called for object: "
              << this << RESET << std::endl;
}

BaseFile::BaseFile(FILE *f) : file(f)
{
    if (!file)
    {
        throw std::runtime_error("Error in constructor. Failed to open file");
    }
    std::cout << BLUE
              << "BaseFile parameterized constructor (with *FILE) called for object: "
              << this << RESET << std::endl;
}

BaseFile::~BaseFile()
{
    if (file)
    {
        fclose(file);
        file = nullptr;
    }
    std::cout << YELLOW << "BaseFile destructor called for object: " << this << RESET << std::endl;
}

BaseFile::BaseFile(BaseFile &&moved) : file(moved.file)
{
    moved.file = nullptr;
}

BaseFile &BaseFile::operator=(BaseFile &&moved)
{
    if (this != &moved)
    {
        if (file)
        {
            fclose(file);
        }
        file = moved.file;
        moved.file = nullptr;
    }
    return *this;
}

bool BaseFile::is_open() const
{
    return file != nullptr;
}

bool BaseFile::can_read() const
{
    if (!file)
        return false;
    int c = std::fgetc(file);
    if (c == EOF)
        return false;
    std::ungetc(c, file); // refresh reader position
    return true;
}

bool BaseFile::can_write() const
{
    if (!file)
        return false;
    if (std::fputc(0, file) == EOF)
        return false;
    std::fseek(file, -1, SEEK_CUR); // refresh writer position
    return true;
}

size_t BaseFile::write_raw(const void *buf, size_t n_bytes)
{
    if (!file)
        throw std::runtime_error("File is not open");
    return fwrite(buf, 1, n_bytes, file);
}

size_t BaseFile::read_raw(void *buf, size_t max_bytes)
{
    if (!file)
        throw std::runtime_error("File is not open");
    return fread(buf, 1, max_bytes, file);
}

long BaseFile::tell()
{
    if (!file)
        throw std::runtime_error("File is not open");
    return ftell(file);
}

bool BaseFile::seek(long offset)
{
    if (!file)
        throw std::runtime_error("File is not open");
    return fseek(file, offset, SEEK_SET) == 0;
}

size_t BaseFile::write(const void *buf, size_t n_bytes)
{
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void *buf, size_t max_bytes)
{
    return read_raw(buf, max_bytes);
}