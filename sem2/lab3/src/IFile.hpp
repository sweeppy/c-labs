#include <iostream>
#pragma once

class IFile
{
public:
    virtual ~IFile() {};

    virtual bool can_read() const = 0;
    virtual bool can_write() const = 0;

    virtual size_t write(const void *buf, size_t n_bytes) = 0;
    virtual size_t read(void *buf, size_t max_bytes) = 0;
};
