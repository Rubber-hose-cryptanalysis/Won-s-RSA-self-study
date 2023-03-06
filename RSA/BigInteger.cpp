#include "BigInteger.hpp"

BigInteger::BigInteger() :bit_size(0), array_size(0)
{
	for (int i = 0; i < 1024; i++)
		num[i] = 0;
}

BigInteger::BigInteger(std::string s)
{
	for (int i = 0; i < size(s); i++)
	{
		//num[i]=i번째 hexadecimal. 16진수의 숫자로 표현.

		if (s[size(s) - 1 - i] >= '0' && s[size(s) - 1 - i] <= '9')
			num[i] = (uint8_t)(s[size(s) - 1 - i] - '0');
		else if (s[size(s) - 1 - i] >= 'A' && s[size(s) - 1 - i] <= 'F')
			num[i] = (uint8_t)(s[size(s) - 1 - i] - 'A' + 0xa);
		else if (s[size(s) - 1 - i] >= 'a' && s[size(s) - 1 - i] <= 'f')
			num[i] = (uint8_t)(s[size(s) - 1 - i] - 'a' + 0xa);
		else
			num[i] = -1; //Error
	}

	for (int i = size(s); i < 1024; i++)
		num[i] = 0;

	if (num[size(s) - 1] == 0x0) //가장 큰 자릿수는 0으로 입력하지 말 것.
		bit_size = 0;
	else if (num[size(s) - 1] == 0x1)
		bit_size = size(s) * 4 - 3;
	else if (num[size(s) - 1] >= 0x2 && num[size(s) - 1] <= 0x3)
		bit_size = size(s) * 4 - 2;
	else if (num[size(s) - 1] >= 0x4 && num[size(s) - 1] <= 0x7)
		bit_size = size(s) * 4 - 1;
	else if (num[size(s) - 1] >= 0x8 && num[size(s) - 1] <= 0xf)
		bit_size = size(s) * 4;
	else
		bit_size = -1; //Error

	array_size = size(s);
}

BigInteger::~BigInteger() {}

bool BigInteger::operator<(const BigInteger& x_2048bit)
{
	if (bit_size < x_2048bit.bit_size)
		return true;
	else if (bit_size > x_2048bit.bit_size)
		return false;

	for (int i = array_size - 1; i >= 0; i--)
	{
		if (num[i] < x_2048bit.num[i])
			return true;
		else if (num[i] > x_2048bit.num[i])
			return false;
	}

	return false;
}

bool BigInteger::operator<(const uint8_t& x_8bit)
{
	if (bit_size > 8)
		return false;

	if (num[1] < (x_8bit >> 1))
		return true;
	else if (num[1] > (x_8bit >> 1))
		return false;

	if (num[0] < (x_8bit & 0x0f))
		return true;
	return false;
}

bool BigInteger::operator<=(const BigInteger& x_2048bit)
{
	if (bit_size < x_2048bit.bit_size)
		return true;
	else if (bit_size > x_2048bit.bit_size)
		return false;

	for (int i = array_size - 1; i >= 0; i--)
	{
		if (num[i] < x_2048bit.num[i])
			return true;
		else if (num[i] > x_2048bit.num[i])
			return false;
	}

	return true;
}

bool BigInteger::operator<=(const uint8_t& x_8bit)
{
	if (bit_size > 8)
		return false;

	if (num[1] < (x_8bit >> 1))
		return true;
	else if (num[1] > (x_8bit >> 1))
		return false;

	if (num[0] > (x_8bit & 0x0f))
		return false;
	return true;
}

bool BigInteger::operator==(const BigInteger& x_2048bit)
{
	if (bit_size != x_2048bit.bit_size)
		return false;

	for (int i = 0; i < array_size; i++)
		if (num[i] != x_2048bit.num[i])
			return false;

	return true;
}

bool BigInteger::operator==(const uint8_t& x_8bit)
{
	if (num[0] != (x_8bit & 0x0f))
		return false;

	if (num[1] != (x_8bit >> 1))
		return false;

	return true;
}

bool BigInteger::operator!=(const BigInteger& x_2048bit)
{
	return !(*this == x_2048bit);
}

bool BigInteger::operator!=(const uint8_t& x_8bit)
{
	return !(*this == x_8bit);
}

bool BigInteger::operator>(const BigInteger& x_2048bit)
{
	if (bit_size > x_2048bit.bit_size)
		return true;
	else if (bit_size < x_2048bit.bit_size)
		return false;

	for (int i = array_size - 1; i >= 0; i--)
	{
		if (num[i] > x_2048bit.num[i])
			return true;
		else if (num[i] < x_2048bit.num[i])
			return false;
	}

	return false;
}

bool BigInteger::operator>(const uint8_t& x_8bit)
{
	if (bit_size > 8)
		return true;

	if (num[1] > (x_8bit >> 1))
		return true;
	else if (num[1] < (x_8bit >> 1))
		return false;

	if (num[0] > (x_8bit & 0x0f))
		return true;
	return false;
}

bool BigInteger::operator>=(const BigInteger& x_2048bit)
{
	if (bit_size > x_2048bit.bit_size)
		return true;
	else if (bit_size < x_2048bit.bit_size)
		return false;

	for (int i = array_size - 1; i >= 0; i--)
	{
		if (num[i] > x_2048bit.num[i])
			return true;
		else if (num[i] < x_2048bit.num[i])
			return false;
	}

	return true;
}

bool BigInteger::operator>=(const uint8_t& x_8bit)
{
	if (bit_size > 8)
		return true;

	if (num[1] > (x_8bit >> 1))
		return true;
	else if (num[1] < (x_8bit >> 1))
		return false;

	if (num[0] < (x_8bit & 0x0f))
		return false;
	return true;
}

BigInteger& BigInteger::operator<<(unsigned int lengthof_shift)
{
	if (bit_size + lengthof_shift > 2048) //shift결과 2048bit를 넘어가는 경우(Overflow)
		return *this;

	unsigned int q = lengthof_shift / 4;
	unsigned int r = lengthof_shift % 4;

	for (int i = array_size - 1; i >= 0; i--)
	{
		uint8_t temp = num[i]; //temp를 사용하는 이유: q==0이면 num[i]값이 계속 변하기 때문.

		if (r == 0)
			num[i + q] += temp;
		else if (r == 1)
		{
			num[i + q] += (temp & 0x7) << 1; //각각 1,2,4,8에 해당하는 bit중 8에 해당하는 bit만 다음 array로 옮기고 나머지는 1칸씩 상승.

			if (i + q == 511)
				break;

			num[i + q + 1] += (temp & 0x8) >> 3;
		}
		else if (r == 2)
		{
			num[i + q] += (temp & 0x3) << 2; //4,8에 해당하는 bit를 다음 array로 옮기고 나머지는 2칸씩 상승.

			if (i + q == 511)
				break;

			num[i + q + 1] += (temp & 0xc) >> 2;
		}
		else if (r == 3)
		{
			num[i + q] += (temp & 0x1) << 3; //2,4,8에 해당하는 bit를 다음 array로 옮기고 나머지(1)는 3칸 상승.

			if (i + q == 511)
				break;

			num[i + q + 1] += (temp & 0xe) >> 1;
		}

		num[i] -= temp;
	}

	bit_size += lengthof_shift;
	array_size = (int)ceil((float)bit_size / (float)4);

	return *this;
}

BigInteger& BigInteger::operator=(const BigInteger& x_2048bit)
{
	for (int i = 0; i < 1024; i++)
		num[i] = x_2048bit.num[i];

	bit_size = x_2048bit.bit_size;
	array_size = x_2048bit.array_size;

	return *this;
}

BigInteger& BigInteger::operator=(const uint8_t& x_8bit)
{
	num[0] = x_8bit & 0x0f;
	if ((x_8bit&0x0f) == 0x0)
	{
		bit_size = 0;
		array_size = 0;
	}
	else if ((x_8bit & 0x0f) == 0x1)
	{
		bit_size = 1;
		array_size = 1;
	}
	else if ((x_8bit & 0x0f) >= 0x2 && (x_8bit & 0x0f) <= 0x3)
	{
		bit_size = 2;
		array_size = 1;
	}
	else if ((x_8bit & 0x0f) >= 0x4 && (x_8bit & 0x0f) <= 0x7)
	{
		bit_size = 3;
		array_size = 1;
	}
	else if ((x_8bit & 0x0f) >= 0x8 && (x_8bit & 0x0f) <= 0xf)
	{
		bit_size = 4;
		array_size = 1;
	}

	num[1] = x_8bit >> 1;
	if ((x_8bit >> 1) == 0x1)
	{
		bit_size = 5;
		array_size = 2;
	}
	else if ((x_8bit >> 1) >= 0x2 && (x_8bit >> 1) <= 0x3)
	{
		bit_size = 6;
		array_size = 2;
	}
	else if ((x_8bit >> 1) >= 0x4 && (x_8bit >> 1) <= 0x7)
	{
		bit_size = 7;
		array_size = 2;
	}
	else if ((x_8bit >> 1) >= 0x8 && (x_8bit >> 1) <= 0xf)
	{
		bit_size = 8;
		array_size = 2;
	}

	return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& x_2048bit)
{
	uint8_t C = 0x0;

	for (int i = 0; i <= (int)fmax(array_size + 1, x_2048bit.array_size + 1); i++)
	{
		if (num[i] + x_2048bit.num[i] + C > 0xf)
		{
			num[i] = num[i] + x_2048bit.num[i] + C - 0x10;
			C = 0x1;
		}

		else
		{
			num[i] = num[i] + x_2048bit.num[i] + C;
			C = 0x0;
		}

		if (array_size <= i + 1 && num[i] != 0)
		{
			array_size = i + 1;

			if (num[i] == 0x1)
				bit_size = 4 * array_size - 3;
			else if (num[i] >= 0x2 && num[i] <= 0x3)
				bit_size = 4 * array_size - 2;
			else if (num[i] >= 0x4 && num[i] <= 0x7)
				bit_size = 4 * array_size - 1;
			else if (num[i] >= 0x8 && num[i] <= 0xf)
				bit_size = 4 * array_size;
		}

		if (i == 511)
			break;
	}

	return *this;
}

BigInteger& BigInteger::operator+=(const uint8_t& x_8bit)
{
	uint8_t C = 0x0;
	uint8_t x0 = x_8bit & 0x0f, x1 = x_8bit & 0xf0;

	if (num[0] + x0 > 0xf)
	{
		C = 0x1;
		num[0] = num[0] + x0 - 0x10;
	}
	else
		num[0] += x0;

	if (num[0] == 0x1)
		bit_size = 1;
	else if (num[0] >= 0x2 && num[0] <= 0x3)
		bit_size = 2;
	else if (num[0] >= 0x4 && num[0] <= 0x7)
		bit_size = 3;
	else if (num[0] >= 0x8 && num[0] <= 0xf)
		bit_size = 4;


	if (num[1] + x1 + C > 0xf)
	{
		num[1] = num[1] + x1 + C - 0x10;
		C = 0x1;
	}
	else
	{
		num[1] = num[1] + x1 + C;
		C = 0x0;
	}

	if (num[1] == 0x1)
		bit_size = 5;
	else if (num[1] >= 0x2 && num[1] <= 0x3)
		bit_size = 6;
	else if (num[1] >= 0x4 && num[1] <= 0x7)
		bit_size = 7;
	else if (num[1] >= 0x8 && num[1] <= 0xf)
		bit_size = 8;

	int temp = array_size;
	for (int i = 2; i <= (int)fmax(temp + 1, 2); i++)
	{
		if (num[i] + C > 0xf)
		{
			num[i] = num[i] + C - 0x10;
			C = 0x1;
		}

		else
		{
			num[i] += C;
			C = 0x0;
			break;
		}

		if (num[i] != 0)
			array_size = i + 1;

		if (i == 511)
			break;
	}

	if (num[array_size - 1] == 0x1)
		bit_size = 4 * array_size - 3;
	else if (num[array_size - 1] >= 0x2 && num[array_size - 1] <= 0x3)
		bit_size = 4 * array_size - 2;
	else if (num[array_size - 1] >= 0x4 && num[array_size - 1] <= 0x7)
		bit_size = 4 * array_size - 1;
	else if (num[array_size - 1] >= 0x8 && num[array_size - 1] <= 0xf)
		bit_size = 4 * array_size;

	return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& x_2048bit)
{
	if (*this < x_2048bit) //항상 더 작은 수만 빼도록 구현. (만약 modular 연산에서 더 큰 수를 빼야한다면, 뺄셈의 순서를 바꾸고 -1을 곱해준다.)
	{
		bit_size = -1; //Error
		return *this;
	}
	
	uint8_t D = 0x0;
	bit_size = 0; //뺄셈으로 인해 바뀌는 bit의 길이를 계산하기 위해 초기화.

	for (int i = 0; i <= (int)fmax(array_size, x_2048bit.array_size); i++)
	{
		if (num[i] < x_2048bit.num[i] + D)
		{
			num[i] = num[i] + 0x10 - x_2048bit.num[i] - D;
			D = 0x1;
		}

		else
		{
			num[i] = num[i] - x_2048bit.num[i] - D;
			D = 0x0;
		}

		if (num[i] == 0x1)
			bit_size = 4 * i + 1;
		else if (num[i] >= 0x2 && num[i] <= 0x3)
			bit_size = 4 * i + 2;
		else if (num[i] >= 0x4 && num[i] <= 0x7)
			bit_size = 4 * i + 3;
		else if (num[i] >= 0x8 && num[i] <= 0xf)
			bit_size = 4 * i + 4;

		if (i == 511)
			break;
	}

	array_size = (int)ceil((float)bit_size / (float)4);

	return *this;
}

BigInteger& BigInteger::operator-=(const uint8_t& x_8bit)
{
	if (*this < x_8bit)
	{
		bit_size = -1; //Error
		return *this;
	}

	uint8_t D = 0x0;
	bit_size = 0; //뺄셈으로 인해 바뀌는 bit의 길이를 계산하기 위해 초기화.

	if (num[0] < (x_8bit & 0x0f))
	{
		num[0] = num[0] + 0x10 - (x_8bit & 0x0f);
		D = 0x1;
	}
	else
	{
		num[0] = num[0] - (x_8bit & 0x0f);
	}

	if (num[0] == 0x1)
		bit_size = 1;
	else if (num[0] >= 0x2 && num[0] <= 0x3)
		bit_size = 2;
	else if (num[0] >= 0x4 && num[0] <= 0x7)
		bit_size = 3;
	else if (num[0] >= 0x8 && num[0] <= 0xf)
		bit_size = 4;

	if (num[1] < (x_8bit >> 1) + D)
	{
		num[1] = num[1] + 0x10 - (x_8bit >> 1) - D;
		D = 0x1;
	}
	else
	{
		num[1] = num[1] - (x_8bit >> 1) - D;
		D = 0x0;
	}

	if (num[1] == 0x1)
		bit_size = 5;
	else if (num[1] >= 0x2 && num[1] <= 0x3)
		bit_size = 6;
	else if (num[1] >= 0x4 && num[1] <= 0x7)
		bit_size = 7;
	else if (num[1] >= 0x8 && num[1] <= 0xf)
		bit_size = 8;

	for (int i = 2; i <= (fmax)(array_size, 2); i++)
	{
		if (num[i] < D)
		{
			num[i] = num[i] + 0x10 - D;
			D = 0x1;
		}

		else
		{
			num[i] -= D;
			D = 0x0;
		}

		if (num[i] == 0x1)
			bit_size = 4 * i + 1;
		else if (num[i] >= 0x2 && num[i] <= 0x3)
			bit_size = 4 * i + 2;
		else if (num[i] >= 0x4 && num[i] <= 0x7)
			bit_size = 4 * i + 3;
		else if (num[i] >= 0x8 && num[i] <= 0xf)
			bit_size = 4 * i + 4;

		if (i == 511)
			break;
	}

	array_size = (int)ceil(bit_size / 4);

	return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& x_2048bit)
{
	//x_2048bit의 각 bit가 1이면 더하고, 0이면 더하지 않는다. 더하기 전에 x_2048bit의 해당 bit의 위치만큼 shift를 해준다.
	if (bit_size + x_2048bit.bit_size - 1 > 2048) //두 수의 곱의 bit길이는 각각의 길이의 합. Overflow가 일어나면 연산 불가.
		return *this;

	BigInteger sum("0");
	int cnt = 0; //현재의 bit위치. 덧셈 전에 얼마나 shift해줘야 하는 지에 대한 값이다.

	for (int i = 0; i < x_2048bit.array_size; i++)
	{
		uint8_t x0 = x_2048bit.num[i] & 0x1, x1 = (x_2048bit.num[i] & 0x2) >> 1, x2 = (x_2048bit.num[i] & 0x4) >> 2, x3 = (x_2048bit.num[i] & 0x8) >> 3; //x0, x1, x2, x3는 각각 num[i]의 bit들.

		if (x0 == 0x1)
		{
			BigInteger temp = *this;
			temp << cnt;

			sum += temp;
		}
		cnt++;

		if (x1 == 0x1)
		{
			BigInteger temp = *this;
			temp << cnt;

			sum += temp;
		}
		cnt++;

		if (x2 == 0x1)
		{
			BigInteger temp = *this;
			temp << cnt;

			sum += temp;
		}
		cnt++;

		if (x3 == 0x1)
		{
			BigInteger temp = *this;
			temp << cnt;

			sum += temp;
		}
		cnt++;
	}

	*this = sum;
	return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& x_2048bit)
{
	BigInteger cnt("0");

	while (*this >= x_2048bit)
	{
		*this -= x_2048bit;
		cnt += 1;
	}

	*this = cnt;
	return *this;
}

BigInteger& BigInteger::operator/=(const uint8_t& x_8bit)
{
	BigInteger cnt("0");

	while (*this >= x_8bit)
	{
		*this -= x_8bit;
		cnt += 1;
	}

	*this = cnt;
	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& x_2048bit)
{
	BigInteger q = *this;
	q /= x_2048bit;

	*this -= q;
	return *this;
}

BigInteger& BigInteger::operator%=(const uint8_t& x_8bit)
{
	while ((*this) >= x_8bit)
		(*this) -= x_8bit;

	return *this;
}

uint8_t BigInteger::operator[](int idx)
{
	if (idx > 2048)
		return 2; //Error

	uint8_t result = num[idx / 4];

	if (idx % 4 == 0)
		result = result & 0x1;
	else if (idx % 4 == 1)
		result = (result & 0x2) >> 1;
	else if (idx % 4 == 2)
		result = (result & 0x4) >> 2;
	else if (idx % 4 == 3)
		result = (result & 0x8) >> 3;

	return result;
}

int BigInteger::bit_length() const
{
	return bit_size;
}

void BigInteger::Printnum_hexadecimal() const
{
	std::string s;
	s.resize(array_size);

	for (int i = array_size - 1; i >= 0; i--)
	{
		char c;

		if (num[i] >= 0x0 && num[i] <= 0x9)
			c = (char)(num[i] + '0');
		else if (num[i] >= 0xa && num[i] <= 0xf)
			c = (char)(num[i] - 0xa + 'A');

		s[array_size - 1 - i] = c;
	}

	std::cout << s << '\n';
}