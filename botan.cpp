#include <cstdio>
#include <ctime>
#include <botan/cast256.h>

#include "botan.h"

bool BotanTest::encrypt(int rounds) {
	int i;
	for (i = 0; i < rounds; i++) {
		Botan::CAST_128 alg;

		alg.set_key((byte*)key, key_size());
		alg.encrypt_n((byte*)in, (byte*)out, data_size() / alg.block_size());
	}
	return true;
}
bool BotanTest::decrypt(int rounds) {
	int i;
	for (i = 0; i < rounds; i++) {
		Botan::CAST_128 alg;

		alg.set_key((byte*)key, key_size());
		alg.decrypt_n((byte*)in, (byte*)out, data_size() / alg.block_size());
	}
	return true;

}
