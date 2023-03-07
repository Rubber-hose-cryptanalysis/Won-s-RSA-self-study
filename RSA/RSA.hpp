#pragma once
//고려대학교 김원이 만든 RSA암호입니다.
//RSA의 KeyGen/Encryption/Decryption 함수를 GMP library를 이용해 구현한 프로그램입니다.

#ifndef __RSA_HPP__
#define __RSA_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "gmp.h"
#include "gmpxx.h"

//Functions
std::vector<mpz_class> keyGen(std::vector<mpz_class>& v);
mpz_class Encrypt(mpz_class m, mpz_class e, mpz_class n);
mpz_class Decrypt(mpz_class c, mpz_class d, mpz_class n);
#endif

/*
References

1. Behrouz Forouzan, Cryptography and Network Security, 3rd Edition
2. Kenneth H. Rosen, Elementary Number Theory and Its Application, 6th Edition
3. NIST Special Publication 800-78-2, Cryptographic Algorithms and Key Sizes for Personal Identity Verification
4. GNU MP 6.2.1 Manual
5. PG Colloquium, The RSA cryptosystem and its pitfalls, September 24th 2014
6. Wikipedia - RSA(cryptosystem)
*/