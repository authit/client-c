#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <gpgme.h>

#include "gpg_opts.h"
#include "error.h"
#include "debug.h"
#include "init.h"

#ifndef MAXLEN
#define MAXLEN 4096
#define SENTENCE "I swear it is true"
#endif

void encrypt (
  gpgme_ctx_t * context,
  telem_gpg_opts * options,
  int num_keys,
  char ** key_path
);
