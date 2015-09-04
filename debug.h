#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include <gpgme.h>

void print_import_result (gpgme_import_result_t r);
const char * nonnull (const char *s);
