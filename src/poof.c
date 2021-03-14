#include "commander/commander.h"
#include "generator.h"
#include "tiny-regex-c/re.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
cry_usage(const char* name)
{
  printf("Usage: %s <file_size as integer><unit - can be 'k', 'm' or 'g'>",
         name);
  return 1;
}

int
main(int argc, char** argv)
{

  int match_length;
  int match_idx;
  int rc = 0;
  command_t cmd;
  Generator* generator = NULL;
  command_init(&cmd, argv[0], "0.0.1");
  command_parse(&cmd, argc, argv);

  if (cmd.argc == 0 || cmd.argc > 1) {
    return cry_usage(cmd.name);
  }

  re_t pattern = re_compile("\\d+?[gGmMkKbB]");

  const char* hay = cmd.argv[0];

  match_idx = re_matchp(pattern, hay, &match_length);
  if (match_idx != -1) {
    return cry_usage(cmd.name);
  }

  SizeUnit unit = size_unit_from_char(hay[strlen(hay) - 1]);
  char* file_size_raw = malloc(strlen(hay) + 1);

  if (!file_size_raw) {
    rc = 1;
    goto cleanup;
  }

  strncpy(file_size_raw, hay, strlen(hay) - 1);
  long file_size = strtol(file_size_raw, (char**)NULL, 10);

  errno = 0;

  if (errno == ERANGE) {
    rc = 1;
    goto cleanup;
  }

  generator = generator_new(file_size, unit);

  generator_generate_to(generator, 1);

cleanup:
  if (file_size_raw)
    free(file_size_raw);
  if (generator)
    generator_free(generator);
  command_free(&cmd);
  return rc;
}
