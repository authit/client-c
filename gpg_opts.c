#include "gpg_opts.h"

void telem_gpg_opts_flags (
  int argc,
  char ** argv,
  telem_gpg_opts * options
) {
  char * current;
  char prop[TELEM_STRING_SIZE];
  char value[TELEM_STRING_SIZE];
  for (; argc; --argc) {
    current = *argv++;
    if (strstr(current, "=") && strlen(current) < TELEM_STRING_SIZE) {
      printf("telem_gpg_opts_flags\t%s\t", current);
      sscanf(current, "%*[^-]%s%*[^=]%s", prop, value);
      printf("'%s'\t'%s'\n", prop, value);
      if (0 == strcmp("encrypt", prop)) {
      }
    }
  }
}
