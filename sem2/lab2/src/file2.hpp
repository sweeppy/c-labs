#include "IFile.hpp"

class Base32File2 : public IFile
{
private:
    IFile *file;

public:
    Base32File2(IFile *file);

    ~Base32File2();

    bool can_read() const;
    bool can_write() const;

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);
};

class RleFile2 : public IFile
{
private:
    IFile *file;

public:
    RleFile2(IFile *file);

    ~RleFile2();

    bool can_read() const;
    bool can_write() const;

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);
};
