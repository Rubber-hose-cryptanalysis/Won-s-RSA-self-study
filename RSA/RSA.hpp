#pragma once
//고려대학교 김원이 만든 RSA암호입니다.
//RSA의 각 과정에서 필요한 연산, RSA의 KeyGen/Encryption/Decryption 함수를 구현한 헤더파일입니다.

#ifndef __RSA_HPP__
#define __RSA_HPP__

#include "BigInteger.hpp"
#include <random>
#include <cstdlib>
#include <ctime>
#include "gmp.h"
#include "gmpxx.h"

//Operations
std::vector<mpz_class> keyGen(std::vector<mpz_class>& v);
mpz_class Encrypt(mpz_class m, mpz_class e, mpz_class n);
mpz_class Decrypt(mpz_class c, mpz_class d, mpz_class n);
#endif