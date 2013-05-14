
LDFLAGS += -lcryptopp -lbotan-1.10 -lgcrypt -Wl,-wrap,malloc 
CXXFLAGS += -I/usr/include/botan-1.10 -O2 -Wall -march=corei7-avx -Wl,-wrap,malloc -g

all: crypto_bench_test

crypto_bench_test: crypto_bench.o botan.o gcrypt.o cryptopp.o
	g++ -o $@ $^ $(LDFLAGS) 
	
clean:
	rm *.o crypto_bench_test

