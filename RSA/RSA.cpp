#include "RSA.hpp"

std::vector<mpz_class> keyGen(std::vector<mpz_class>& v)
{
	mpz_class e; /*mpz_init(e);*/ mpz_set_ui(e.get_mpz_t(), 0x10001); //public key e값 생성.
	mpz_class n; //mpz_init(n); //public key n값 initialize
	mpz_t p, q; mpz_init(p); mpz_init(q); //distinct prime p,q

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, (96889010407 * time(NULL) + 1013904223) % (unsigned long)pow(2, 31) - 1);

	mpz_t temp; mpz_init(temp);

	mpz_set_ui(p, 1);
	for (int i = 0; i < 1023; i++)
	{
		mpz_mul_2exp(p, p, 1);

		mpz_urandomb(temp, state, 1);
		mpz_add(p, p, temp);
	}
	mpz_nextprime(p, p); //p는 1024bit prime

	mpz_set_ui(q, 1);
	for (int i = 0; i < 1024; i++)
	{
		mpz_mul_2exp(q, q, 1);

		mpz_urandomb(temp, state, 1);
		mpz_add(q, q, temp);
	}
	mpz_nextprime(q, q); //q는 1025bit prime

	mpz_mul(n.get_mpz_t(), p, q); //n=p*q. 2048bit public key.
	
	mpz_t phi; mpz_init(phi); mpz_sub_ui(p, p, 1); mpz_sub_ui(q, q, 1); mpz_mul(phi, p, q); //Euler_phi(n)=(p-1)*(q-1)
	mpz_class d; //mpz_init(d);
	mpz_invert(d.get_mpz_t(), e.get_mpz_t(), phi);

	mpz_clear(p); mpz_clear(q); mpz_clear(temp); gmp_randclear(state);

	v[0] = e; v[1] = n; v[2] = d;
	return v;
}

mpz_class Encrypt(mpz_class m, mpz_class e, mpz_class n)
{
	mpz_class c;

	mpz_powm(c.get_mpz_t(), m.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
	return c;
}

mpz_class Decrypt(mpz_class c, mpz_class d, mpz_class n)
{
	mpz_class m;

	mpz_powm(m.get_mpz_t(), c.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
	return m;
}