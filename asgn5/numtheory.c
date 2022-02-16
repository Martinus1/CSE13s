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
	mpz_t r, nr, t , nt, asgn, q;
	mpz_init_set(r, n);
	mpz_init_set(nr, a);
	mpz_init_set_ui(t, 0);
	mpz_init_set_ui(nr, 1);
	mpz_init(asgn);
	mpz_init(q);

	mpz_t temp_r, temp_t;
	mpz_init(temp_t);
	mpz_init(temp_r);


	while (mpz_cmp_ui(r, 0) != 0) {
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
		mpz_clears(r, nr, t, nt, q);
        	mpz_clears(temp_r, temp_t);
		return;
	} else if (mpz_cmp_ui(t, 0) < 0) {
		//t = t + n
		mpz_add(t,t, n);
	}

	//CLEAR VARS
	mpz_set(i, t);
	mpz_clears(r, nr, t, nt, q);
	mpz_clears(temp_r, temp_t);
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
			mpz_mul(out, out ,p);
			mpz_mod(out, out, modulus);
		}
		
		//p = (p * p) mod n;
		mpz_mul(temp_p, p, p);
		mpz_mod(p, temp_p, modulus);
			
		//d = (d / 2);
		mpz_div_ui(exponent, exponent, 2);
	}
	
	mpz_clears(p, temp_p);
	//We take the Out value now
	return;
}

bool is_prime(mpz_t n, uint64_t iters) {
	//CHeck if n = 2
	if (mpz_cmp_ui(n,2) == 0) {
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
	mpz_t temp_n, temp_r, nn, a,s, two,  temp_s, y, r, j;
	mpz_init_set(temp_n, n);
	mpz_init(a);
	mpz_init(temp_s);
	mpz_init(y);
	mpz_init(j);
	mpz_init_set_ui(s, 0);
	mpz_init_set_ui(two, 2);
	// r = r - 1
	mpz_init_set(r, n);
	mpz_sub_ui(r, r, 1);
	mpz_init_set(temp_r, r);

	// nn = n - 1
	mpz_init_set(nn, n);
	mpz_sub_ui(nn,nn, 1);

	//Write n-1 2^s r such that r is odd
	// determine  r, count = s
	//uint64_t count = 0;
	
	// do while r % 2 = 0
	while (mpz_cmp_ui(temp_r, 0) != 0) {
		mpz_div_ui(r, r, 2);
		//count += 1;
		mpz_add_ui(s, s, 1);
		mpz_set(temp_r, r);
		mpz_mod_ui(temp_r, temp_r,  2);
	}

	//Start with i = 1 or i = 0?
	for(uint64_t i = 0; i < iters; i+= 1) {
		//random from (2...n-2)
		gmp_randstate_t state;
		gmp_randinit_mt(state);
		gmp_randseed_ui(state, 1234);
		//randomb? or randomm, randomn
		mpz_urandomb(a, state, 512);
		//a = (a % (n - 2)) + 2;
		mpz_sub_ui(temp_n, temp_n, 2);
		mpz_mod(a, a,  temp_n);
		mpz_add_ui(a, a, 2);
		

		//y = power_mod(a, r, n);
		pow_mod(y, a, r, n);
		
		//This just sets nn = n - 1; nn will not be changed
		mpz_sub_ui(nn, n, 1);
		if (mpz_cmp_ui(y, 1) != 0  && mpz_cmp(y,nn) != 0) {
			mpz_set_ui(j, 1);
			mpz_sub_ui(temp_s, s, 1);
			while(mpz_cmp(j, temp_s) >= 0  && mpz_cmp(y,nn) != 0) {
				pow_mod(y,y,two,n);
				mpz_set(y, y);
				if (mpz_cmp_ui(y , 1) == 0) {
					gmp_printf(" %Zd = NotPrime \n");
					mpz_clears(temp_n, temp_s, temp_r, a, y, r, j, nn);
					return false;
				}
				mpz_add_ui(j,j,1);
			}		
			
			if (mpz_cmp(y, nn) != 0) {
				gmp_printf(" %Zd = NotPrime \n");
				mpz_clears(temp_n, temp_s, temp_r, a, y, r, j, nn);
				return false;
			}		
		}
	}

	mpz_clears(temp_n, temp_s, temp_r, a, y, j, r, nn);
	return true;
		
}
/*
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
	
	gmp_randstate_t state;
        gmp_randstate_mt(state);
        gmp_randseed_ui(state, 1234);

        //not randomb
        mpz_urandomm(a, state, 512);
}
*/
