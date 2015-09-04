#include "encrypt.h"

void encrypt (
  gpgme_ctx_t * context,
  authit_gpg_opts * options,
  int num_files,
  char ** file_list
  )
{
  char * p;
  char * pSource;
  size_t read_bytes;
  gpgme_error_t err;
  gpgme_data_t source;
  gpgme_data_t dest;

  pSource = file_list[0];

  //get key to encrypt, get the first key
  gpgme_key_t key[2];
  err = gpgme_op_keylist_start(*context, options->send_to, 0);
  err = gpgme_op_keylist_next (*context, key);
  if (err) {
    printf("Key not found in current key-ring: %s\n", options->send_to);
    return;
  }
  key[1] = 0; //set to NULL the second entry

  //point to source buffer
  err = gpgme_data_new_from_mem(&source, pSource, strlen(pSource), 0);
  if (err != GPG_ERR_NO_ERROR) {
    printf("Error in reading data to encrypt.\n");
    fail_if_err(err);
  }

  //create dest buffer
  err = gpgme_data_new(&dest);
  if (err != GPG_ERR_NO_ERROR) {
    printf("Error in creating output data buffer to encrypt.\n");
    fail_if_err(err);
  }

  //encrypt text
  gpgme_encrypt_flags_t flags;
  flags = GPGME_ENCRYPT_NO_ENCRYPT_TO | GPGME_ENCRYPT_ALWAYS_TRUST; //only specified recipient, no defaults please
  err = gpgme_op_encrypt(*context, key, flags, source, dest);
  if (err != GPG_ERR_NO_ERROR) {
    printf("Error in encrypting data.\n");
    fail_if_err(err);
  }

  p = gpgme_data_release_and_get_mem(dest, &read_bytes);

  p[read_bytes] = 0;

  //retrieve result
  printf("Result: \n%s\n", p);

  //release key and buffers
  gpgme_key_release(key[0]);
  gpgme_data_release(source);
}
