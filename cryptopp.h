#ifndef CRYPTOPP_TEST
#define CRYPTOPP_TEST

#include "crypto_bench.h"

#include "cryptopp/cryptlib.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/ccm.h"
#include "cryptopp/cast.h"

// Cipher Mode
#define CIPHER_MODE CBC_Mode
// Ciphers
#define CIPHER CAST128

using namespace CryptoPP;
using CryptoPP::CBC_Mode;
using CryptoPP::CAST256;

class CryptoppTest : public CryptoBenchTest {
public:
	CryptoppTest() {
		name = "Cryptopp CAST128";
		::memset(in, 0x73, sizeof(in));
	}
	virtual inline ssize_t	data_size() {
		return sizeof(in);
	}
	virtual inline ssize_t key_size() {
		return CryptoPP::CIPHER::DEFAULT_KEYLENGTH;
	}
	virtual inline bool encrypt(int rounds) {
		int i;
		for (i = 0; i < rounds; i++) {
			encrypt_round();
		}
		return true;
	}	
	virtual inline bool decrypt(int rounds) {
		int i;
		for (i = 0; i < rounds; i++) {
			decrypt_round();
		}
		return true;
	}

	virtual inline bool prepare() {
		return true;
	}
	void encrypt_round();
	void decrypt_round();
protected:
	unsigned char key[CryptoPP::CIPHER::DEFAULT_KEYLENGTH];
	unsigned char decrypted[4096];
	size_t        out_sz;
};

#endif
