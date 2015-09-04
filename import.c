#include "import.h"

void import (
  gpgme_ctx_t * context,
  authit_gpg_opts * options,
  int num_keys,
  char ** key_path
  )
{
  gpgme_error_t err;
  int url_mode = 0;
  int nul_mode = 0;
  gpgme_import_result_t impres;
  gpgme_data_t data;

  for (; num_keys; --num_keys, key_path++)
    {
      printf ("reading file `%s'\n", *key_path);
      err = gpgme_data_new_from_file(&data, *key_path, 1);
      fail_if_err(err);

      if (url_mode)
        gpgme_data_set_encoding(
          data,
          (nul_mode? GPGME_DATA_ENCODING_URL0 : GPGME_DATA_ENCODING_URL)
        );

      err = gpgme_op_import(*context, data);
      fail_if_err(err);
      impres = gpgme_op_import_result(*context);
      if (!impres)
      {
        fprintf(stderr, "No import result returned\n");
        exit(1);
      }
      print_import_result(impres);
      if (options != NULL && 0 == strcmp(options->sign, "true")) {
        sign(context, options->me);
      }

      gpgme_data_release(data);
    }
}

void sign (
  gpgme_ctx_t * context,
  char * lookup
  )
{
  gpgme_error_t err;
  // Get key to encrypt, get the first key
  gpgme_key_t key[2];
  err = gpgme_op_keylist_start(*context, lookup, 0);
  err = gpgme_op_keylist_next (*context, key);
  if (err) {
    printf("Key not found in current key-ring: %s\n", lookup);
    return;
  }
  key[1] = 0; //set to NULL the second entry
  err = gpgme_signers_add (*context, key[0]);
  fail_if_err (err);
  gpgme_key_unref (key[0]);
}
