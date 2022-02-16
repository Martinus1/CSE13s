#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <ncurses.h>
#include <unistd.h>
#include <gmp.h>
#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"



int main() {

	uint64_t iters = 100;
	//while ((opt = getopt(argc, argv, "tsn:i:o:")) != -1) {
	//	switch(opt) {
		
	//	}
	//}
	
	mpz_t a, b, c, d, e;
	mpz_init_set_ui(a, 1);
	mpz_init_set_ui(b, 2);
	mpz_init_set_ui(c, 4);
	mpz_init_set_ui(d, 7);
	mpz_init_set_ui(e, 269);
	is_prime(a, iters);
	is_prime(b, iters);
	is_prime(c, iters);
	is_prime(d, iters);
	is_prime(e, iters);

	return 0;
}
