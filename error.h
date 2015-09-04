#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include <gpgme.h>

#define fail_if_err(err)                                        \
  do                                                            \
    {                                                           \
      if (err)                                                  \
        {                                                       \
          fprintf (stderr, "%s:%d: %s: %s (%d.%d)\n",           \
                   __FILE__, __LINE__, gpgme_strsource (err),   \
                   gpgme_strerror (err),                        \
                   gpgme_err_source (err), gpgme_err_code (err)); \
          exit (1);                                             \
        }                                                       \
    }                                                           \
  while (0)
