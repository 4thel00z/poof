#include "generator.h"
#include "random_string.h"

SizeUnit
size_unit_from_char(char c)
{
  switch (c) {
    case 'b':
    case 'B': {
      return Byte;
    }
    case 'k':
    case 'K': {
      return Kilobyte;
    }
    case 'm':
    case 'M': {
      return Megabyte;
    }
    case 'g':
    case 'G': {
      return Gigabyte;
    }
  }

  return Byte;
}

Generator*
generator_new(int file_size, SizeUnit unit)
{
  Generator* g = malloc(sizeof(*g));
  g->file_size = file_size;
  g->unit = unit;
  return g;
}

void
generator_free(Generator* g)
{
  if (g) {
    free(g);
  }
}

long long
calc_min(long long a, long long b)
{
  if (a < b)
    return a;
  return b;
}

int
generator_generate_to(Generator* generator, int fd)
{

  long long max_size = generator->file_size * generator->unit;
  size_t next_buffer_size = calc_min(GENERATOR_BUFFER_SIZE, max_size);
  int rc = 0;

  char* current_buffer =
    malloc(sizeof(*current_buffer) * (GENERATOR_BUFFER_SIZE + 1));

  if (!current_buffer) {
    rc = GENERATE_ERROR_OOM;
    goto cleanup;
  }

  if (next_buffer_size < 0) {
    rc = GENERATE_ERROR_LT_ZERO;
    goto cleanup;
  }

  while (max_size > 0) {
    random_string(current_buffer, next_buffer_size);
    write(fd, current_buffer, next_buffer_size);
    max_size -= next_buffer_size;
  }

cleanup:
  if (current_buffer)
    free(current_buffer);

  return rc;
}
