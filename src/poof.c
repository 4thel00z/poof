#include <stdio.h>
#include "commander/commander.h"

enum SizeUnit{
  Byte = 0,
  Kilobyte = 1,
  Megabyte = 2,
  Gigabyte = 3
};

typedef struct {
  int file_size;
  SizeUnit unit;
} Generator;

int file_size;
char * cp_file_size;
char * cp_unit;

static void
verbose(command_t *self) {
  printf("verbose: enabled\n");
}

static void
required(command_t *self) {
  printf("required: %s\n", self->arg);
}

static void
optional(command_t *self) {
  printf("optional: %s\n", self->arg);
}

int
main(int argc, char **argv){
  command_t cmd;
  command_init(&cmd, argv[0], "0.0.1");
  command_option(&cmd, "-v", "--verbose", "enable verbose stuff", verbose);
  command_option(&cmd, "-r", "--required <arg>", "required arg", required);
  command_option(&cmd, "-o", "--optional [arg]", "optional arg", optional);
  command_parse(&cmd, argc, argv);
  printf("additional args:\n");
  for (int i = 0; i < cmd.argc; ++i) {
    printf("  - '%s'\n", cmd.argv[i]);
  }
  command_free(&cmd);
  return 0;
}