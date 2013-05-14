#ifndef AF_ALG_TEST
#define AF_ALG_TEST

#include <cstdio>
#include <ctime>

#include "crypto_bench.h"
#include <cstdio>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <assert.h>

#include <linux/if_alg.h>

#define SOL_ALG 279


class AF_ALGTest : public CryptoBenchTest {
public:
	AF_ALGTest() {
		name = "AF_ALG CAST128";
	}
	virtual ~AF_ALGTest() {
		
	}
	virtual inline ssize_t	data_size() {
		return sizeof(in);
	}
	virtual inline ssize_t key_size() {
		return 16;
	}
	virtual inline bool encrypt(int rounds) {
		return do_operation(ALG_OP_ENCRYPT, rounds);
	}
	virtual inline bool decrypt(int rounds) {
		return do_operation(ALG_OP_DECRYPT, rounds);
	}
	virtual bool prepare() {
		return true;
	}
	bool do_operation(int op, int rounds);
};

#endif
