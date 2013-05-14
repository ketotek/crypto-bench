#ifndef CRYPTO_BENCH_H
#define CRYPTO_BENCH_H

#include <sys/types.h>

#define KEY_SIZE 16

class CryptoBenchTest {
public:
	const char		*name;
	virtual bool		prepare() = 0;
	virtual bool		encrypt(int rounds) = 0;
	virtual bool		decrypt(int rounds) = 0;
	virtual ssize_t		data_size() = 0;
	virtual ssize_t		key_size() = 0;
protected:
	unsigned char		in[4096];
	unsigned char		out[4096];
	unsigned char		key[KEY_SIZE];

};

void run_benchmark(CryptoBenchTest *test, int rounds);

#endif
