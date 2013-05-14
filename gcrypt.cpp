#include <stdio.h>
#include <gcrypt.h>
#include <assert.h>

#include "crypto_bench.h"
#include "gcrypt.h"

#define GCRY_CIPHER GCRY_CIPHER_CAST5
#define GCRY_C_MODE GCRY_CIPHER_MODE_CBC

void GCryptTest::encrypt_round() {
	gcry_error_t     gcryError;
	gcry_cipher_hd_t gcryCipherHd;

	gcryError = gcry_cipher_open(&gcryCipherHd, GCRY_CIPHER, GCRY_C_MODE, 0);
	if (gcryError) {
		printf("gcry_cipher_open failed:  %s/%s\n",
		       gcry_strsource(gcryError),
		       gcry_strerror(gcryError));
		return;
	}

	gcryError = gcry_cipher_setkey(gcryCipherHd, key, key_size());
	if (gcryError) {
		printf("gcry_cipher_setkey failed:  %s/%s\n",
		       gcry_strsource(gcryError),
		       gcry_strerror(gcryError));
		return;
	}

	gcryError = gcry_cipher_encrypt(gcryCipherHd, out, data_size(),
				        in, data_size());
	if (gcryError) {
		printf("gcry_cipher_encrypt failed:  %s/%s\n",
		       gcry_strsource(gcryError),
		       gcry_strerror(gcryError));
		return;
	}
}

void GCryptTest::decrypt_round() {
	gcry_error_t     gcryError;
	gcry_cipher_hd_t gcryCipherHd;

	gcryError = gcry_cipher_open(&gcryCipherHd, GCRY_CIPHER, GCRY_C_MODE, 0);
	if (gcryError) {
		printf("gcry_cipher_open failed:  %s/%s\n",
		       gcry_strsource(gcryError),
		       gcry_strerror(gcryError));
		return;
	}

	gcryError = gcry_cipher_setkey(gcryCipherHd, key, key_size());
	if (gcryError) {
		printf("gcry_cipher_setkey failed:  %s/%s\n",
		       gcry_strsource(gcryError),
		       gcry_strerror(gcryError));
		return;
	}

	gcryError = gcry_cipher_decrypt(gcryCipherHd, out, data_size(),
					in, data_size());
	if (gcryError) {
		printf("gcry_cipher_encrypt failed:  %s/%s\n",
		       gcry_strsource(gcryError),
		       gcry_strerror(gcryError));
		return;
	}
}
