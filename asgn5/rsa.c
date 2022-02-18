#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
	//INITIALZIE VARS
	mpz_t lambda_n, temp_q, temp_p;
	mpz_inits(lambda_n, temp_q, temp_p, NULL);
	//Set Range [nbits/4, ((3*nbits) / 4)]
	uint64_t pbits = ((random() % ((nbits / 4) - 1)) + ( 3 * (nbits / 4)));
	uint64_t qbits = (nbits - pbits);
	
	//Generates Primes -> p,q
	make_prime(p, pbits, iters);
	make_prime(q, qbits, iters);
	
	//DISCORD COMMENT
	mpz_mul(n, p, q);

	mpz_sub_ui(temp_q, q, 1);
        mpz_sub_ui(temp_p, p, 1);

	lcm(lambda_n, temp_p, temp_q);
	
	while (mpz_cmp_ui(temp_p, 1) != 0 ) {
		mpz_urandomb(e , state, nbits);
		mpz_set(temp_q, e);
		gcd(temp_p, lambda_n , temp_q);		
	}
	
	mpz_clears(temp_p, temp_q, lambda_n, NULL);
	
	return;
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
	gmp_fprintf(pbfile, "%Zx\n", n);
	gmp_fprintf(pbfile, "%Zx\n", e);
	gmp_fprintf(pbfile, "%Zx\n", s);
	fprintf(pbfile, "%s\n", username);
	
	return;
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
	gmp_fscanf(pbfile, "%Zx\n", n);
	gmp_fscanf(pbfile, "%Zx\n", e);
	gmp_fscanf(pbfile, "%Zx\n", s);
	fscanf(pbfile, "%s\n", username);
	
	return;
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
	
	mpz_t lambda_n, temp_p, temp_q;
	mpz_inits(lambda_n, temp_p, temp_q, NULL);
	
	// q - 1 and p - 1
	mpz_sub_ui(temp_q, q, 1);
        mpz_sub_ui(temp_p, p, 1);

	lcm(lambda_n, temp_p, temp_q);
	mod_inverse(d, e, lambda_n);
	mpz_clears(lambda_n, temp_p, temp_q, NULL);
	return;
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
	gmp_fprintf(pvfile, "%Zx\n", n);
	gmp_fprintf(pvfile, "%Zx\n", d);

	return;
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
	gmp_fscanf(pvfile, "%Zx\n", n);
	gmp_fscanf(pvfile, "%Zx\n", d);
	
	return;
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
	pow_mod(c, m, e, n);

	return;
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
	mpz_t j, c;
	mpz_inits(j, c, NULL);
	
	//Block Size
	uint32_t k = ((mpz_sizeinbase(n, 2) - 1) / 8);
	//Array that can hold k-bytes aka block
	uint8_t *arr = ((uint8_t *)  calloc(k, sizeof(uint8_t)));
	while (fread(arr + 1, sizeof(uint8_t), k - 1, infile) > 0) {
		//needs to be 0xff, so we can know where does the block start
		arr[0] = 0xff;
		mpz_import(j, k, 1, sizeof(arr[0]), 1, 0, arr);
		rsa_encrypt(c, j, e, n);
		gmp_fprintf(outfile, "%Zx", c);
	}

	mpz_clears(j,c, NULL);
	return;
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
	pow_mod(m,c,d,n);
	
	return;
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
	//INIT VARS
	mpz_t m, c;
	mpz_inits(m, c, NULL);
	
	//k: Block Size -> k = (log2(n)-1 ) / 8
	uint32_t k;
	//j: Number of bites actually converted
	uint64_t j;

	k = ((mpz_sizeinbase(n, 2) - 1) / 8);
	uint8_t *arr = (uint8_t *) calloc(k, sizeof(uint8_t));

	while (gmp_fscanf(infile, "%Zx\n", c) != EOF) {
		gmp_printf("%Zd\n", c);
		gmp_printf("%Zd\n", d);
		gmp_printf("%Zd\n", n);

		rsa_decrypt(m, c, d,n);
		mpz_export(arr, &j, 1, sizeof(uint8_t), 1, 0, m);
		fwrite(arr + 1, sizeof(uint8_t), j - 1, outfile);
	}


	mpz_clears(c, m, NULL);
	return;
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
	pow_mod(s,m,d,n);

	return;
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
	mpz_t t;
	mpz_init(t);
	pow_mod(t, s, e, n);
	if ((mpz_cmp(t, m) == 0)) {
		return true;
	}
	
	mpz_clear(t);
	return false;
}
