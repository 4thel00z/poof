#include "random_string.h"

void
random_string(char* string, size_t length)
{
  char pool[] =
    "^°!\"§$%&/"
    "()=?0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  size_t poolsize = strlen(pool);
  size_t index;
  size_t i;

  srand((unsigned)time(NULL));

  for (i = 0; i < length; ++i) {
    index = rand() % poolsize; // a random index into the pool
    string[i] = pool[index];   // take that character
  }

  string[i] = '\0';
}
