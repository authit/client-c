#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Options for telem_gpg
#ifndef TELEM_OPT
#define TELEM_OPT 1

#define TELEM_STRING_SIZE 200

// Defaults for linux
  #define TELEM_OPT_KEYRING_DIR "../../keys/client/keyring_dir"
  #define TELEM_OPT_SEND_TO "First Last"


typedef struct telem_gpg_opts_struct {
  char keyring_dir[TELEM_STRING_SIZE];
  char send_to[TELEM_STRING_SIZE];
} telem_gpg_opts;

#endif

void telem_gpg_opts_flags (
  int argc,
  char ** argv,
  telem_gpg_opts * options
);
