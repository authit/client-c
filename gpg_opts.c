#include "gpg_opts.h"

void authit_gpg_opts_flags (
  int argc,
  char ** argv,
  authit_gpg_opts * options
) {
  char * current;
  char prop[AUTHIT_STRING_SIZE];
  char value[AUTHIT_STRING_SIZE];
  for (; argc; --argc) {
    current = *argv++;
    strcpy(prop, "");
    strcpy(value, "");
    if (strnlen(current, AUTHIT_STRING_SIZE) > AUTHIT_STRING_SIZE &&
      !strstr(current, "=") &&
      !strstr(current, "--")
      )
    {
      continue;
    }
    sscanf(current, "--%[^=]=%s", prop, value);
    // If these are empty the flag is not valid
    if (strnlen(prop, AUTHIT_STRING_SIZE) < 1)
    {
      continue;
    }
    if (strnlen(value, AUTHIT_STRING_SIZE) < 1)
    {
      strcpy(value, "true");
    }
    printf("'%s'\t'%s'\n", prop, value);
    if (0 == strcmp("encrypt", prop)) {
    }
  }
}
