#ifndef BOTAN_TEST
#define BOTAN_TEST

#include <cstdio>
#include <ctime>
#include <botan/cast128.h>

#include "crypto_bench.h"

using namespace Botan;

class BotanTest : public CryptoBenchTest {
public:
	BotanTest() {
		name = "Botan CAST128";
	}
	virtual inline ssize_t	data_size() {
		return sizeof(in);
	}
	virtual inline ssize_t key_size() {
		return 16;
	}
	virtual inline bool prepare() {
		return true;
	}
	virtual bool encrypt(int rounds);
	virtual bool decrypt(int rounds);
};

#endif
