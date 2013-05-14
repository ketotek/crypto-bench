#ifndef GCRYPT_TEST
#define GCRYPT_TEST

class GCryptTest : public CryptoBenchTest {
public:
	GCryptTest() {
		name = "gcrypt CAST128";
	}
	virtual inline ssize_t	data_size() {
		return sizeof(in);
	}
	virtual inline ssize_t key_size() {
		return 16;
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
};

#endif
