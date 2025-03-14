#include <iostream>
#include <cstdio>

#define DEFAULT_TABLE "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456"
class BaseFile
{
private:
    FILE *file;

public:
    BaseFile();
    BaseFile(const char *path, const char *mode);
    BaseFile(FILE *f);

    ~BaseFile();

    bool is_open() const;
    bool can_read() const;
    bool can_write() const;

    size_t write_raw(const void *buf, size_t n_bytes);
    size_t read_raw(void *buf, size_t max_bytes);
    long tell();
    bool seek(long offset);

    virtual size_t write(const void *buf, size_t n_bytes);
    virtual size_t read(void *buf, size_t max_bytes);
};

class Base32File : public BaseFile
{
private:
    const char *table;

public:
    Base32File(const char *path, const char *mode, const char *customTable = DEFAULT_TABLE);
    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t max_bytes);

private:
    size_t encoded32_size(int raw_size);
    size_t decoded32_size(int encode_size);

    int encode32(const char *raw_data, int raw_size, char *dst);
    int decode32(const char *encoded_data, int encoded_size, char *dst);
};

class RleFile : public BaseFile
{
public:
    RleFile(const char *path, const char *mode);
    size_t write(const void *buf, size_t n_bytes);
    // size_t read(void *buf, size_t max_bytes);

private:
    char *encode(const char *data, size_t data_size, size_t &output_size);
    // int decode(const char *data, size_t data_size, const char *dst);
};
