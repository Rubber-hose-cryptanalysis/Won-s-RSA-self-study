#pragma once
//������б� ����� ���� RSA��ȣ�Դϴ�.
//RSA�� �� �������� �ʿ��� ����, RSA�� KeyGen/Encryption/Decryption �Լ��� ������ ��������Դϴ�.

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