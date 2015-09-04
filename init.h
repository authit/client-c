#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <sys/stat.h>

#include <gpgme.h>

#include "gpg_opts.h"
#include "error.h"

void setup(gpgme_ctx_t * context, telem_gpg_opts * options);
void setup_options(telem_gpg_opts * options);
void mkdirs(const char *dir);
