#include "init.h"


void setup(gpgme_ctx_t * context, authit_gpg_opts * options) {
  gpgme_error_t error;
  // gpgme_engine_info_t info;

  /* Initializes gpgme */
  gpgme_check_version (NULL);

  /* Initialize the locale environment.  */
  setlocale (LC_ALL, "");
  gpgme_set_locale (NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));
#ifdef LC_MESSAGES
  gpgme_set_locale (NULL, LC_MESSAGES, setlocale (LC_MESSAGES, NULL));
#endif

  error = gpgme_new(context);
  fail_if_err(error);
  /* Setting the output type must be done at the beginning */
  gpgme_set_armor(*context, 1);

  /* Check OpenPGP */
  // error = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
  // fail_if_err(error);
  // error = gpgme_get_engine_info (&info);
  // fail_if_err(error);
  // while (info && info->protocol != gpgme_get_protocol(*context)) {
  //   info = info->next;
  // }
  // /* TODO: we should test there *is* a suitable protocol */
  // fprintf (stderr, "Engine OpenPGP %s is installed at %s\n", info->version,
	//    info->file_name); /* And not "path" as the documentation says */

  // Use options
  if (options == NULL) {
    return;
  }
  // Create the keyring is it doesnt exist
  mkdirs(options->keyring);

  /* Initializes the context */
  error = gpgme_ctx_set_engine_info(
    *context,
    GPGME_PROTOCOL_OpenPGP,
    NULL,
    options->keyring
  );
  fail_if_err(error);
}

void mkdirs(const char *dir) {
  char tmp[256];
  char *p = NULL;
  size_t len;

  snprintf(tmp, sizeof(tmp),"%s",dir);
  len = strlen(tmp);
  if(tmp[len - 1] == '/')
    tmp[len - 1] = 0;
  for(p = tmp + 1; *p; p++)
    if(*p == '/') {
      *p = 0;
      mkdir(tmp, S_IRWXU);
      *p = '/';
    }
  mkdir(tmp, S_IRWXU);
}
