#ifndef BIGINTEGERALGORITHMS_H
#define BIGINTEGERALGORITHMS_H

#include "BigInteger.hh"
#include <string>

using namespace std;

/* Some mathematical algorithms for big integers.
 * This code is new and, as such, experimental. */

// Returns the greatest common divisor of a and b.
int random(int a,int b);
BigUnsigned BigInt_Random(int lenght);
BigInteger BigInt_Random_1(int leng);
BigUnsigned gcd(BigUnsigned a, BigUnsigned b);
BigInteger  gcd(BigInteger a, BigInteger b); // BigInterger Version
BigInteger pow(BigInteger a,BigInteger n);
BigUnsigned pow(BigUnsigned a,BigUnsigned n);
BigUnsigned a_powx_modn(BigUnsigned x,BigUnsigned b,BigUnsigned n);
BigInteger a_powx_modn(BigInteger x,BigInteger b,BigInteger n);
BigUnsigned Mod_Inverse(BigUnsigned n,BigUnsigned p);
BigInteger Mod_Inverse(BigInteger n,BigInteger p);
BigUnsigned get_k(BigUnsigned a);
BigUnsigned get_q(BigUnsigned a);
int Miller_Rabin(BigUnsigned p,int loop=1);
string DectoHex(BigUnsigned a);
BigUnsigned HextoDec(string str);


/* Extended Euclidean algorithm.
 * Given m and n, finds gcd g and numbers r, s such that r*m + s*n == g. */
void extendedEuclidean(BigInteger m, BigInteger n,
		BigInteger &g, BigInteger &r, BigInteger &s);

/* Returns the multiplicative inverse of x modulo n, or throws an exception if
 * they have a common factor. */
BigUnsigned modinv(const BigInteger &x, const BigUnsigned &n);

// Returns (base ^ exponent) % modulus.
BigUnsigned modexp(const BigInteger &base, const BigUnsigned &exponent,
		const BigUnsigned &modulus);

#endif
