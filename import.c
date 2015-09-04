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

      gpgme_data_release(data);
    }
}
