
#include "cryptopp.h"
#include <iostream>

void CryptoppTest::encrypt_round()
{
	byte iv[CryptoPP::CIPHER::BLOCKSIZE];

	::memset( key, 0x01, CryptoPP::CIPHER::DEFAULT_KEYLENGTH );
	::memset(  iv, 0x01, CryptoPP::CIPHER::BLOCKSIZE );

	std::string cipher((const char*)out);

	CBC_Mode< CAST128 >::Encryption e;
	e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

	StringSource s(in, sizeof(in), true, 
		       new StreamTransformationFilter(e, new StringSink(cipher),
		                                      StreamTransformationFilter::NO_PADDING));
	out_sz = cipher.size();
}

void CryptoppTest::decrypt_round()
{
	byte iv[CryptoPP::CIPHER::BLOCKSIZE];

	::memset( key, 0x01, CryptoPP::CIPHER::DEFAULT_KEYLENGTH );
	::memset(  iv, 0x01, CryptoPP::CIPHER::BLOCKSIZE );

	std::string cipher((const char*)out, out_sz);
	std::string dec((const char*)decrypted);

	CBC_Mode< CAST128 >::Decryption d;
	d.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

	StringSource s(cipher, true, 
		       new StreamTransformationFilter(d, new StringSink(dec),
						      StreamTransformationFilter::NO_PADDING));
}
