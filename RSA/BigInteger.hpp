#pragma once
//������б� ����� ���� RSA��ȣ�Դϴ�.
//C/C++���� �����ϴ� ������ �ִ� ũ�Ⱑ �ʹ� �۾� ū ������ �����ϱ� ���� ��������Դϴ�.

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
	uint8_t num[1024]; //BigInteger, array�� �̿��� �� ĭ�� 4bit�� ���� �����Ͽ� 2048bit�� ǥ��. array size�� 512�� �ƴ� 1024�� ������ ���� ���� �� ������ ������ ���� ����.
	int bit_size; //bitlength of BigInteger
	int array_size; //size of num[]. �Լ� ���� �� ����� ���Ǹ� ���� ����.

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

	uint8_t operator[](int idx); //idx��° bit ��ȯ.

	//Member functions
	int bit_length() const;
	void Printnum_hexadecimal() const;
};

#endif