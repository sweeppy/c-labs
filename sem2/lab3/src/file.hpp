#include <iostream>
#include "IFile.hpp"

#define DEFAULT_TABLE "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456"
class BaseFile : public IFile
{
private:
    FILE *file;

public:
    BaseFile();
    BaseFile(const char *path, const char *mode);
    BaseFile(FILE *f);

    virtual ~BaseFile();

    BaseFile(const BaseFile &) = delete;
    BaseFile &operator=(const BaseFile &) = delete;

    BaseFile(BaseFile &&moved);
    BaseFile &operator=(BaseFile &&moved);

    bool is_open() const;
    bool can_read() const;
    bool can_write() const;

    size_t write_raw(const void *buf, size_t n_bytes);
    size_t read_raw(void *buf, size_t max_bytes);
    long tell();
    bool seek(long offset);

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);
};