#include "RSA.hpp"

int main()
{
	std::vector<mpz_class> v;
	v.resize(3);
	
	keyGen(v);

	gmp_printf("The public keys are (%ZX, %ZX)\n", v[0], v[1]);

	mpz_class m;
	mpz_set_str(m.get_mpz_t(), "189d813790ba0891371897314f8ff1320e31e9b32c1cac4386765723910ce4b1e37e", 16); //Example
	gmp_printf("The plaintext is %ZX\n", m);

	mpz_class c;
	c = Encrypt(m, v[0], v[1]);
	gmp_printf("The ciphertext is %ZX\n", c);

	m = Decrypt(c, v[2], v[1]);
	gmp_printf("The plaintext is %ZX\n", m);

	return 0;
}