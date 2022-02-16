#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <ncurses.h>
#include <unistd.h>
#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"



int main(int argc, char **argv) {

	uint64_t iters = 100
	//while ((opt = getopt(argc, argv, "tsn:i:o:")) != -1) {
	//	switch(opt) {
		
	//	}
	//}
	
	mpz_t a, b, c, d, e;
	mpz_init_set(a, 1);
	mpz_init_set(b, 2);
	mpz_init_set(c, 4);
	mpz_init_set(d, 7);
	mpz_init_set(e, 269);
	is_prime(a, iters);
	is_prime(b, iters);
	isprint(c, iters);
	isprint(d, iters);
	isprint(e, iters);

	return;
}
