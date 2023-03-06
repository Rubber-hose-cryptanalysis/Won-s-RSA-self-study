#pragma once
//고려대학교 김원이 만든 RSA암호입니다.
//C/C++에서 제공하는 정수의 최대 크기가 너무 작아 큰 정수를 구현하기 위한 헤더파일입니다.

#ifndef __BIG_INTEGER_HPP__
#define __BIG_INTEGER_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class BigInteger
{
private:
	//private variable members
	uint8_t num[1024]; //BigInteger, array를 이용해 한 칸당 4bit씩 값을 저장하여 2048bit를 표현. array size가 512가 아닌 1024인 이유는 제곱 연산 시 컴파일 에러를 막기 위함.
	int bit_size; //bitlength of BigInteger
	int array_size; //size of num[]. 함수 정의 시 계산의 편의를 위해 정의.

public:
	//Constructors / Destructors
	BigInteger();
	BigInteger(std::string s);
	~BigInteger();

	//Operators
	bool operator<(const BigInteger& x_2048bit);
	bool operator<(const uint8_t& x_8bit);
	bool operator<=(const BigInteger& x_2048bit);
	bool operator<=(const uint8_t& x_8bit);
	bool operator==(const BigInteger& x_2048bit);
	bool operator==(const uint8_t& x_8bit);
	bool operator!=(const BigInteger& x_2048bit);
	bool operator!=(const uint8_t& x_8bit);

	bool operator>(const BigInteger& x_2048bit);
	bool operator>(const uint8_t& x_8bit);
	bool operator>=(const BigInteger& x_2048bit);
	bool operator>=(const uint8_t& x_8bit);

	BigInteger& operator<<(unsigned int lengthof_shift);
	// BigInteger& operator>>(unsigned int lengthof_shift);

	BigInteger& operator=(const BigInteger& x_2048bit);
	BigInteger& operator=(const uint8_t& x_8bit);
	BigInteger& operator+=(const BigInteger& x_2048bit);
	BigInteger& operator+=(const uint8_t& x_8bit);
	BigInteger& operator-=(const BigInteger& x_2048bit);
	BigInteger& operator-=(const uint8_t& x_8bit);
	BigInteger& operator*=(const BigInteger& x_2048bit);
	// BigInteger& operator*=(const uint8_t& x_8bit);
	BigInteger& operator/=(const BigInteger& x_2048bit);
	BigInteger& operator/=(const uint8_t& x_8bit);
	BigInteger& operator%=(const BigInteger& x_2048bit);
	BigInteger& operator%=(const uint8_t& x_8bit);

	uint8_t operator[](int idx); //idx번째 bit 반환.

	//Member functions
	int bit_length() const;
	void Printnum_hexadecimal() const;
};

#endif