#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <gmp.h>


void gcd(mpz_t d, mpz_t a, mpz_t b) {
	
	while ((mpz_cmp_d(b,0)) != 0) {
		mpz_set(d, b);
		mpz_mod(b, a, b);
		mpz_set(a, d);
	}

	return;

}

//define LCM

void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
	
	//INITIALIZE VARS
	mpz_t r, nr, t , nt;
	mpz_init_set(r, n);
	mpz_init_set(nr, n);
	mpz_init_set(t, 0);
	mpz_init_set(nr, 1);

	mpz_t temp_r, temp_t;
	mpz_init(temp_t);
	mpz_init(temp_r);


	while (mpz_cmp_d(r, 0) != 0) {
		//do floor division
		mpz_fdiv_ui(q, r, nr);
		
		//simmultaneous assignement
		//mpz_t temp_r = r;
		//r = nr;
		//nr = temp_r - (q * nr);
		mpz_set(temp_r, r);
		mpz_set(r, nr);
		//IS THIS UI?
		mpz_sub_ui(nr, temp_r, mpz_mul(nr, q, nr));


		//simmultaneous assignement
                //mpz_t temp_t = t;
                //t = nt;
                //nt = temp_t - (q * nt);
		mpz_set(temp_t, t);
                mpz_set(t, nt);
		//IS THIS UI?
                mpz_sub_ui(nt, temp_t, mpz_mul(nt, q, nt));
	}
	

	if (mpz_cmp(r) > 0) {
		//NO inverse -> Clear Vars
		mpz_set(i, 0);
		mpz_clears(r, nr, t, nt);
        	mpz_clears(temp_r, temp_t);
		return;
	} else if (mpz_cmp(t) < 0) {
		//t = t + n
		mzp_add(t, t, n);
	}

	//CLEAR VARS
	mpz_set(i, t);
	mpz_clears(r, nr, t, nt);
	mpz_clears(temp_r, temp_t);
}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
	
	mpz_t p;
	mzp_init_set(p, base);
	mzp_set_ui(out, 1);

	while ((mpz_cmp_d(exponent)) > 0) {
		//check if d-exponent is odd
		if (mpz_odd_p(exponent) > 0) {
		 	//v = (v * p) mod n
			mzp_mul(out, out ,p);
			gmp_mod(out, out, modulus);
		}
		
		//p = (p * p) mod n;
		mpz_mod(p, mzp_mul(p, p,p), modulus);
			
		//d = (d / 2);
		mpz_div_ui(exponent, exponent, 2);
	}
	
	mpz_clear(p);
	//We take the Out value now
	return;
}

bool is_prime(mpz_t n, uint64_t iters) {
	//CHeck if n = 2
	if (mpz_cmp_d(n,2) == 0) {
		gmp_printf(" %Zd = prime \n");
		return true;
	}
	
	//check is n is even
	//FIND IF X > 0
	if(mpz_even_p(n) != 0) {
		gmp_printf(" %Zd = NotPrime \n");
		return false;
	}
	
	//INITIALIZE VARS
	mpz_t temp_n, temp_r, nn, a, temp_s, y, r;
	mpz_init_set(temp_n, n);
	mpz_init(a);
	mpz_init(temp_s);
	mpz_init(y);
	// r = r - 1
	mpz_init_set(r, n);
	mpz_sub(r, r, 1);
	mpz_init_set(temp_r, r);

	// nn = n - 1
	mpz_init_set(nn, n);
	mpz_sub(nn,nn, 1);

	//Write n-1 2^s r such that r is odd
	// determine  r
	uint64_t count = 0;
	
	// do while r % 2 = 0
	while (mpz_cmp(temp_r, 0) != 0) {
		mpz_div(r, r, 2);
		count += 1;
		mpz_set(temp_r, r);
		mpz_mod(temp_r, temp_r,  2);
	}

	//Start with i = 1 or i = 0?
	for(uint64_t i == 0; i < iters; i+= 1) {
		//random from (2...n-2)
		gmp_randstate_t state;
		gmp_randstate_t(state);
		gmp_randseed_ui(state, 1234);
		mpz_urandomm(a, state, 512);
		//a = (a % (n - 2)) + 2;
		mpz_sub(temp_n, temp_n, 2);
		mpz_mod(a, a,  temp_n);
		mpz_add(a, a, 2);
		

		//y = power_mod(a, r, n);
		mpz_set(y,power_mod(a, r, n));

		//This just sets nn = n - 1; nn will not be changed
		mpz_sub(nn, n, 1);
		if (mpz_cmp(y, 1) != 0  && mpz_cmp(y,nn) != 0) {
			mpz_set(j, 1);
			mpz_sub(temp_s, s, 1);
			while(mpz_cmp(j, temp_s) >= 0  && mpz_cmp(y,nn) != 0) {
				mpz_set(y, power_mod(y,2,n));
				if (mpz_cmp(y , 1) == 0) {
					gmp_printf(" %Zd = NotPrime \n");
					mpz_clears(temp_n, temp_s, temp_r, a, y, r, nn);
					return false;
				}
				mpz_add(j,j,1);
			}		
			
			if (mpz_cmp(y, nn) != 0) {
				gmp_printf(" %Zd = NotPrime \n");
				mpz_clears(temp_n, temp_s, temp_r, a, y, r, nn);
				return false;
			}		
		}
	}

	mpz_clears(temp_n, temp_s, temp_r, a, y, r, nn);
	return true;
		
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
	
	gmp_randstate_t state;
        gmp_randstate_t(state);
        gmp_randseed_ui(state, 1234);

        //not randomb
        mpz_urandomm(a, state, 512);
}
