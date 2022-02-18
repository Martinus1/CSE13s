#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <ncurses.h>
#include <sys/stat.h>
#include <unistd.h>
#include <gmp.h>
#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"

int main(int argc, char **argv) {

	int opt = 0;
	uint64_t bits = 266;
	uint64_t iters = 50;
	char *pub_file = "rsa.pub";
	char *priv_file = "rsa.priv";
	bool isVerbose = false;
	int seed_name;
	bool isSeedRandom = true;
	bool isHelp = false;
	
	while ((opt = getopt(argc, argv, "b:i:n:s:vh")) != -1) {
        	switch (opt) {
        	case 'b':
           		 //specify min bits to pub modulus n
            		bits = atoi(optarg);
           		break;
       		case 'i':
        	    	//specifies the number of Miller-Rabin iterations for testing primes (default: 50)
        		iters = atoi(optarg);
        		break;
	        case 'n':
	      		//specifies the public key file (default: rsa.pub)
	       		pub_file = optarg;
			break;
		case 'd':
                        //specifies the private key file (default: rsa.priv)
                        priv_file = optarg;
			break;
		case 's':
		       	//specifies random seed 
     			seed_name = atoi(optarg);
			isSeedRandom = false;			
     	 		break;
    	   	 case 'v':
			//enables Verbose Output
  	     		isVerbose = true;
        	   	break;	
		 case 'h':
                       	//Print Program Synopsis/Usage
                        isHelp = true;
			break;
        	default: return 1;
       		}
   	}
	
	 
	//PRINT SYNOPSIS/USAGE
	if (isHelp == true) {
		printf("SYNOPSIS\n");
                printf("Generates an RSA public/private key pair\n\n");

                 printf("USAGE\n");
                 printf("./keygen [OPTIONS]\n\n");

                printf("OPTIONS\n");
                printf("-h Print Program Synopsis/Usage\n");
                printf("-v enables Verbose Output\n");
		printf("-b bits     Min bits neededfor public key n (default: 256) \n");
                printf("-i iterations   specifies the number of iterations\n");
		printf("-n pbfile   Public key file(default rsa.pub)");
                printf("-d pvfile   Private Key file(default: rsa.priv)\n");
                printf("-s seed     Specifies random seed \n");
	}
	
	//INIT VARS
	mpz_t p, q, n, e, d, s, username, sign;
	mpz_inits(p, q, n, e, d, s,  username, sign, NULL);
	
	// Open public and private key files
	FILE *pubfile = fopen(pub_file, "w");
	FILE *privfile = fopen(priv_file, "w");
	
	if (pubfile == NULL) {
   		printf("There has been a problem opening the public key file");
 		return 1;
	}

	if (privfile == NULL) {
		printf("There has been a problem opening the public key file");
		return 1;
	}
	//make private key file pemissions set to 0600
	//wtf is mode?
	fchmod(fileno(pubfile), 0600);
	

	//Initialize Random State
	if (isSeedRandom == false) {
		randstate_init(seed_name);
	} else {
		//Seed is random
		randstate_init(time(NULL));
	}

	//make public and private keys
	rsa_make_pub(p, q, n , e ,bits, iters);
	rsa_make_priv(d, e, p ,q);

	//Get user's name as a string
	char *name;
	name = getenv("USER");
	mpz_set_str(username, name, 62);

	//Compute the signature of the username
	rsa_sign(s, username, d, n);

	//Write computed public and private key with their respected files
	rsa_write_pub(n, e, s, name, pubfile);
	rsa_write_priv(n, d, privfile);

	//Print for verbose if specified
	if(isVerbose) {
		printf("user = %s\n", name);
		gmp_printf("s (%d bits) = %Zd \n", mpz_sizeinbase(username, 2), username);
		gmp_printf("p (%d bits) = %Zd \n", mpz_sizeinbase(p, 2), p);
		gmp_printf("q (%d bits) = %Zd \n", mpz_sizeinbase(q, 2), q);
		gmp_printf("n (%d bits) = %Zd \n", mpz_sizeinbase(n, 2), n);
		gmp_printf("e (%d bits) = %Zd \n", mpz_sizeinbase(e, 2), e);
		gmp_printf("d (%d bits) = %Zd \n", mpz_sizeinbase(d, 2), d);
	}

	//Close Files, Clean Randstate
	fclose(pubfile);
	fclose(privfile);
	randstate_clear();
	mpz_clears(p, q, n, e, d, s, username, sign, NULL);
	
	return 0;
}
