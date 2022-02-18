#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <gmp.h>
#include "numtheory.h"
#include "randstate.h"

//GCD OF a, b -> stored in d
void gcd(mpz_t d, mpz_t a, mpz_t b) {

    while ((mpz_cmp_d(b, 0)) != 0) {
        mpz_set(d, b);
        mpz_mod(b, a, b);
        mpz_set(a, d);
    }

    return;
}

//LCM OF a, b -> stored in d
void lcm(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t top, gcd_val;
    mpz_init(top);
    mpz_init(gcd_val);
    mpz_mul(top, a, b);

    mpz_abs(top, top);

    gcd(gcd_val, a, b);
    mpz_div(d, top, gcd_val);
    mpz_clears(top, gcd_val, NULL);
    return;
}

void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {

    //INITIALIZE VARS
    mpz_t r, nr, t, nt, asgn, q;
    mpz_init_set(r, n);
    mpz_init(nt);
    mpz_init_set(nr, a);
    mpz_init_set_ui(t, 0);
    mpz_init_set_ui(nt, 1);
    mpz_init(asgn);
    mpz_init(q);

    mpz_t temp_r, temp_t;
    mpz_init(temp_t);
    mpz_init(temp_r);

    while (mpz_cmp_ui(nr, 0) != 0) {
        //do floor division q = quotient
        mpz_fdiv_q(q, r, nr);

        //simmultaneous assignement
        //mpz_t temp_r = r;
        //r = nr;
        //nr = temp_r - (q * nr);
        mpz_set(temp_r, r);
        mpz_set(r, nr);
        mpz_mul(asgn, q, nr);
        mpz_sub(nr, temp_r, asgn);

        //simmultaneous assignement
        //mpz_t temp_t = t;
        //t = nt;
        //nt = temp_t - (q * nt);
        mpz_set(temp_t, t);
        mpz_set(t, nt);
        mpz_mul(asgn, q, nt);
        mpz_sub(nt, temp_t, asgn);
    }

    if (mpz_cmp_ui(r, 1) > 0) {
        //NO inverse -> Clear Vars
        mpz_set_ui(i, 0);
        mpz_clears(r, nr, t, nt, q, NULL);
        mpz_clears(temp_r, temp_t, NULL);
        return;
    } else if (mpz_cmp_ui(t, 0) < 0) {
        //t = t + n
        mpz_add(t, t, n);
    }

    //CLEAR VARS
    mpz_set(i, t);
    mpz_clears(r, nr, t, nt, q, NULL);
    mpz_clears(temp_r, temp_t, NULL);
    return;
}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t p, temp_p;
    mpz_init_set(p, base);
    mpz_set_ui(out, 1);
    mpz_init(temp_p);

    while ((mpz_cmp_ui(exponent, 0)) > 0) {
        //check if d-exponent is odd
        if (mpz_odd_p(exponent) > 0) {
            //v = (v * p) mod n
            mpz_mul(out, out, p);
            mpz_mod(out, out, modulus);
        }

        //p = (p * p) mod n;
        mpz_mul(temp_p, p, p);
        mpz_mod(p, temp_p, modulus);

        //d = (d / 2);
        mpz_div_ui(exponent, exponent, 2);
    }

    mpz_clears(p, temp_p, NULL);
    return;
}

bool is_prime(mpz_t n, uint64_t iters) {
    //Check if n is 2
    if (mpz_cmp_ui(n, 2) == 0) {
        //gmp_printf(" %Zd = prime \n \n", n);
        return true;
    }

    //check is n is even
    if (mpz_even_p(n) != 0) {
        //gmp_printf(" %Zd = NotPrime \n \n", n);
        return false;
    }

    //INITIALIZE VARS
    mpz_t temp_n, temp_r, nn, a, s, two, temp_s, y, r, j;
    mpz_inits(temp_n, temp_r, nn, a, s, two, temp_s, y, r, j, NULL);
    mpz_set(temp_n, n);
    mpz_set_ui(s, 0);
    mpz_set_ui(two, 2);
    // r = r - 1
    mpz_sub_ui(r, n, 1);
    mpz_set_ui(temp_r, 0);

    // nn = n - 1
    mpz_sub_ui(nn, n, 1);

    //Write n-1 = 2^s r such that r is odd
    while (mpz_cmp_ui(temp_r, 0) == 0) {
        mpz_div_ui(r, r, 2);
        mpz_add_ui(s, s, 1);
        mpz_set(temp_r, r);
        mpz_mod_ui(temp_r, temp_r, 2);
        /*
		gmp_printf("Cycle %Zd, ", s);
		gmp_printf("r = %Zd ", r);
		gmp_printf("temp_r = %Zd ", temp_r);
		*/
    }

    //Start with i = 1 or i = 0?
    for (uint64_t i = 0; i < iters; i += 1) {
        //random from (2...n-2)
        randstate_init(time(NULL));
        //gmp_randinit_mt(state);
        //gmp_randseed_ui(state, time(NULL));
        //randomb? or randomm, randomn
        mpz_urandomb(a, state, 512);
        //a = (a % (n - 2)) + 2;
        mpz_sub_ui(temp_n, temp_n, 2);
        mpz_mod(a, a, temp_n);
        mpz_add_ui(a, a, 2);

        //y = power_mod(a, r, n);
        pow_mod(y, a, r, n);

        //This just sets nn = n - 1; nn will not be changed
        mpz_sub_ui(nn, n, 1);
        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, nn) != 0) {
            mpz_set_ui(j, 1);
            mpz_sub_ui(temp_s, s, 1);
            while (mpz_cmp(j, temp_s) >= 0 && mpz_cmp(y, nn) != 0) {
                pow_mod(y, y, two, n);
                mpz_set(y, y);
                if (mpz_cmp_ui(y, 1) == 0) {
                    //	gmp_printf(" %Zd = NotPrime \n \n", n);
                    mpz_clears(temp_n, temp_s, temp_r, two, s, a, y, r, j, nn, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }

            if (mpz_cmp(y, nn) != 0) {
                //gmp_printf(" %Zd = NotPrime \n \n", n);
                mpz_clears(temp_n, temp_s, temp_r, two, a, y, r, s, j, nn, NULL);
                return false;
            }
        }
    }

    //gmp_printf(" %Zd = prime \n \n", n);
    mpz_clears(temp_n, temp_s, temp_r, two, a, y, j, r, s, nn, NULL);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    // n has to be at least bits number of bits long
    // check with n >= 2^b + random number

    //INIT VARS
    mpz_t n, rand, two;
    mpz_inits(n, rand, two, NULL);
    mpz_set_ui(two, 2);

    // this is n = 2 ^ b
    mpz_pow_ui(n, two, bits);

    //random from (2...n-2)
    randstate_init(time(NULL));
    mpz_urandomb(rand, state, bits - 2);
    mpz_add(n, n, rand);

    bool isPrime = false;
    while (isPrime != true) {
        isPrime = is_prime(n, iters);
        mpz_add_ui(n, n, 1);
    }

    mpz_sub_ui(p, n, 1);
    //gmp_printf(" Generated Prime = %Zd \n \n", p);
    mpz_clears(n, rand, two, NULL);
    return;
}
