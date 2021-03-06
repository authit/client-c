#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <gpgme.h>

#include "gpg_opts.h"
#include "error.h"
#include "debug.h"
#include "init.h"

#include "import.h"
#include "encrypt.h"

#ifndef PGM
#define PGM "test-client"
#endif

const char * USAGE[] = {"import keys...", "encrypt files...", "\0"};

int main (int argc, char **argv)
{
  gpgme_ctx_t context;
  authit_gpg_opts options;
  // The function to call
  void (*action)(
    gpgme_ctx_t *,
    authit_gpg_opts *,
    int,
    char **
  ) = NULL;

  // Set the defaults
  authit_gpg_opts_flags_defaults(&options);
  // Set the flags
  authit_gpg_opts_flags(argc, argv, &options);
  // Setup gpgme
  setup(&context, &options);

  argv++;
  if (argc > 2) {
    if (0 == strncmp("import", argv[0], AUTHIT_STRING_SIZE)) {
      action = import;
    } else if (0 == strncmp("encrypt", argv[0], AUTHIT_STRING_SIZE)) {
      action = encrypt;
    }
    if (action != NULL) {
      // Second time argv was incremented, thus removing program name
      // and the action name
      argv++;
      argc -= 2;
      for (; argc && authit_gpg_opts_isflag(argv[0]); --argc) {
        argv++;
      };
      action(
        &context,
        &options,
        argc,
        argv
      );
    }
  } else {
    printf("Options %s\n", PGM);
    int i;
    for (i = 0; USAGE[i][0] != 0; ++i) {
      printf("\t%s\n", USAGE[i]);
    }
  }

  gpgme_release(context);

  return 0;
}
