#include "gpg_opts.h"

void authit_gpg_opts_flags_defaults(authit_gpg_opts * options) {
  strcpy(options->keyring, AUTHIT_OPT_KEYRING_DIR);
  strcpy(options->recv, AUTHIT_OPT_RECV);
  strcpy(options->sign, AUTHIT_OPT_SIGN);
  strcpy(options->me, AUTHIT_OPT_ME);
}

int authit_gpg_opts_isflag(char * flag) {
  if (strnlen(flag, AUTHIT_STRING_SIZE) < AUTHIT_STRING_SIZE &&
    strstr(flag, "=") &&
    strstr(flag, "--")
    )
  {
    return 1;
  }
  return 0;
}

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
    if (!authit_gpg_opts_isflag(current))
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
    if (0 == strcmp("keyring", prop)) {
      strcpy(options->keyring, value);
    } else if (0 == strcmp("recv", prop)) {
      strcpy(options->recv, value);
    } else if (0 == strcmp("me", prop)) {
      strcpy(options->me, value);
    } else if (0 == strcmp("sign", prop)) {
      strcpy(options->sign, value);
    }
  }
}
