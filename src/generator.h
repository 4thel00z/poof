#ifndef __GENERATOR_H__
#define __GENERATOR_H__
#include <stdlib.h>
#include <unistd.h>
#define GENERATOR_BUFFER_SIZE (1024)

// Error codes

#define GENERATE_ERROR_LT_ZERO 1
#define GENERATE_ERROR_OOM 2

typedef enum
{
  Byte = 1,
  Kilobyte = 1024,
  Megabyte = 1048576,
  Gigabyte = 1073741824
} SizeUnit;

typedef struct
{
  long file_size;
  SizeUnit unit;
} Generator;

SizeUnit
size_unit_from_char(char c);

Generator*
generator_new(int file_size, SizeUnit unit);

void
generator_free(Generator* g);

int
generator_generate_to(Generator* generator, int fd);

#endif
