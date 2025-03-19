#include <iostream>

size_t _encoded32_size(int raw_size);
size_t _decoded32_size(int encode_size);
int _encode32(const char *raw_data, int raw_size, char *dst, const char *table);
int _decode32(const char *encoded_data, int encoded_size, char *dst, const char *table);

char *_encodeRLE(const char *data, size_t data_size, size_t &output_size);
int _decodeRLE(const char *data, size_t data_size, char *dst);
