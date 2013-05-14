
#include <ctime>
#include <cstdio>

#include "crypto_bench.h"
#include "gcrypt.h"
#include "botan.h"
#include "cryptopp.h"
#include "af_alg.h"

#define EPS 0.0001
#define N_ROUNDS 50000

static size_t malloc_total = 0;
extern "C" {
	void *__real_malloc(size_t size);

	void *__wrap_malloc(size_t size)
	{
		malloc_total += size;
		return __real_malloc(size);
	}
}

void *operator new(std::size_t size)
{
	return malloc(size);
}

void* operator new[](std::size_t size) {
	return malloc(size);
}

void operator delete(void* ptr) {
	free(ptr);
}

void operator delete[](void* ptr) {
	free(ptr);
}

void run_benchmark(CryptoBenchTest *test, int rounds)
{
	clock_t start, stop;
	float time, speed, mem;
	const char *suffix[] = {"B", "KB", "MB", "GB"};
	int sidx = 0;
	int midx = 0;

	malloc_total = 0;

	start = clock();
	test->encrypt(rounds);
	stop = clock();

	time = (float)(stop - start) / CLOCKS_PER_SEC;
	time = time < EPS ? 1 : time;
	speed = test->data_size() * rounds / time;

	while (speed >= 1024) {
		sidx++;
		speed /= 1024;
	}
	mem = malloc_total;
	while (mem >= 1024) {
		midx++;
		mem /= 1024;
	}

	printf("%20s\tEncrypt\t%8.2f %s/s %8.2f %s\n", test->name, speed, suffix[sidx], mem, suffix[midx]);

	malloc_total = 0;

	start = clock();
	test->decrypt(rounds);
	stop = clock();

	time = (float)(stop - start) / CLOCKS_PER_SEC;
	time = time < EPS ? 1 : time;
	speed = test->data_size() * rounds / time;

	sidx = midx = 0;
	while (speed >= 1024) {
		sidx++;
		speed /= 1024;
	}
	mem = malloc_total;
	while (mem >= 1024) {
		midx++;
		mem /= 1024;
	}

	printf("%20s\tDecrypt\t%8.2f %s/s %8.2f %s\n", test->name, speed, suffix[sidx], mem, suffix[midx]);

}

int main(int argc, char *argv[])
{
	GCryptTest *gctest = new GCryptTest();
	BotanTest *bt = new BotanTest();
	CryptoppTest *cppt = new CryptoppTest();
	AF_ALGTest *aftest = new AF_ALGTest();

	printf("%20s\tOperation\tSpeed\tMemory\n", "Implementation");
	for (int i = 0; i < 60; i++)
		printf("-");
	printf("\n");

	run_benchmark(bt, N_ROUNDS);
	run_benchmark(gctest, N_ROUNDS);
	run_benchmark(cppt, N_ROUNDS);
	run_benchmark(aftest, N_ROUNDS);
}
