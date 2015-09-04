#include "debug.h"

void print_import_result (gpgme_import_result_t r)
{
  gpgme_import_status_t st;

  for (st=r->imports; st; st = st->next)
    {
      printf ("  fpr: %s err: %d (%s) status:", nonnull (st->fpr),
              st->result, gpgme_strerror (st->result));
      if (st->status & GPGME_IMPORT_NEW)
        fputs (" new", stdout);
      if (st->status & GPGME_IMPORT_UID)
        fputs (" uid", stdout);
      if (st->status & GPGME_IMPORT_SIG)
        fputs (" sig", stdout);
      if (st->status & GPGME_IMPORT_SUBKEY)
        fputs (" subkey", stdout);
      if (st->status & GPGME_IMPORT_SECRET)
        fputs (" secret", stdout);
      putchar ('\n');
    }
  printf ("key import summary:\n"
          "        considered: %d\n"
          "        no user id: %d\n"
          "          imported: %d\n"
          "      imported_rsa: %d\n"
          "         unchanged: %d\n"
          "      new user ids: %d\n"
          "       new subkeys: %d\n"
          "    new signatures: %d\n"
          "   new revocations: %d\n"
          "       secret read: %d\n"
          "   secret imported: %d\n"
          "  secret unchanged: %d\n"
          "  skipped new keys: %d\n"
          "      not imported: %d\n",
          r->considered,
          r->no_user_id,
          r->imported,
          r->imported_rsa,
          r->unchanged,
          r->new_user_ids,
          r->new_sub_keys,
          r->new_signatures,
          r->new_revocations,
          r->secret_read,
          r->secret_imported,
          r->secret_unchanged,
          r->skipped_new_keys,
          r->not_imported);
}

const char * nonnull (const char *s)
{
  return s? s :"[none]";
}
