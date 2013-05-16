crypto-bench
============

This is a simple benchmark for the CAST-128 (CAST5) block cipher.
The implementation of the following libraries are used:
* botan
* libgcrypt
* crypto++
* Linux kernel AF_ALG crypto interface

For each implementation the speed of encryption and decryption operations
are measured. Also, dynamic memory allocations are partially accounted for,
but this does not work for most of the library-operation combinations.

Usage
-----
```
$ make
$ ./crypto_bench_test
```
A sample output:
```

      Implementation    Operation       Speed   Memory
 ------------------------------------------------------------
       Botan CAST128    Encrypt    96.69 MB/s   306.86 KB
       Botan CAST128    Decrypt    97.17 MB/s     0.00 B
      gcrypt CAST128    Encrypt    75.70 MB/s     0.00 B
      gcrypt CAST128    Decrypt    76.00 MB/s     0.00 B
    Cryptopp CAST128    Encrypt   101.73 MB/s   412.37 MB
    Cryptopp CAST128    Decrypt   109.73 MB/s   801.47 MB
      AF_ALG CAST128    Encrypt   135.10 MB/s     0.00 B
      AF_ALG CAST128    Decrypt   315.98 MB/s     0.00 B
 ```
