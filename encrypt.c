#include "encrypt.h"

void encrypt (
  gpgme_ctx_t * context,
  telem_gpg_opts * options,
  int num_keys,
  char ** key_path
  )
{
  gpgme_error_t error;
  gpgme_key_t recipients[2] = {NULL, NULL};
  gpgme_data_t clear_text, encrypted_text;
  gpgme_encrypt_result_t  result;
  gpgme_user_id_t user;
  char *buffer;
  ssize_t nbytes;

  error = gpgme_op_keylist_start(*context, options->send_to, 1);
  fail_if_err(error);
  error = gpgme_op_keylist_next(*context, &recipients[0]);
  fail_if_err(error);
  error = gpgme_op_keylist_end(*context);
  fail_if_err(error);

  user = recipients[0]->uids;
  printf("Encrypting for %s <%s>\n", user->name, user->email);

  /* Prepare the data buffers */
  error = gpgme_data_new_from_mem(&clear_text, SENTENCE, strlen(SENTENCE), 1);
  fail_if_err(error);
  error = gpgme_data_new(&encrypted_text);
  fail_if_err(error);

  /* Encrypt */
  error = gpgme_op_encrypt(*context, recipients,
			   GPGME_ENCRYPT_ALWAYS_TRUST, clear_text, encrypted_text);
  fail_if_err(error);
  result = gpgme_op_encrypt_result(*context);
  if (result->invalid_recipients)
    {
      fprintf (stderr, "Invalid recipient found: %s\n",
	       result->invalid_recipients->fpr);
      exit (1);
    }

  nbytes = gpgme_data_seek (encrypted_text, 0, SEEK_SET);
  if (nbytes == -1) {
    fprintf (stderr, "%s:%d: Error in data seek: ",
	     __FILE__, __LINE__);
    perror("");
    exit (1);
    }
  buffer = malloc(MAXLEN);
  nbytes = gpgme_data_read(encrypted_text, buffer, MAXLEN);
  if (nbytes == -1) {
    fprintf (stderr, "%s:%d: %s\n",
	     __FILE__, __LINE__, "Error in data read");
    exit (1);
  }
  buffer[nbytes] = '\0';
  printf("Encrypted text (%i bytes):\n%s\n", (int)nbytes, buffer);
  free(buffer);

  exit(0);
}
