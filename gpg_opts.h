#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Options for authit_gpg
#ifndef AUTHIT_OPT
#define AUTHIT_OPT 1

#define AUTHIT_STRING_SIZE 200

// Defaults for linux
  #define AUTHIT_OPT_KEYRING_DIR "../../keys/client/keyring_dir"
  #define AUTHIT_OPT_SEND_TO "First Last"


typedef struct authit_gpg_opts_struct {
  char keyring_dir[AUTHIT_STRING_SIZE];
  char send_to[AUTHIT_STRING_SIZE];
} authit_gpg_opts;

#endif

void authit_gpg_opts_flags (
  int argc,
  char ** argv,
  authit_gpg_opts * options
);
