#include "IFile.hpp"
#define DEFAULT_TABLE "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456"

class Base32File2 : public IFile
{
private:
    IFile *file;
    const char *table;

public:
    Base32File2(IFile *file, const char *table = DEFAULT_TABLE);

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
