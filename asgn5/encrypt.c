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


int main(int argc, char **argv) {

        int opt = 0;
        char *pub_file = "rsa.pub";
        char *in_file = "stdin";
        char *out_file = "stdout";
        bool isVerbose = false;
        bool isHelp = false;

        while ((opt = getopt(argc, argv, "i:o:n:vh")) != -1) {
                switch (opt) { 
		case 'i':
			in_file = optarg;
			break;
		case 'o':
			out_file = optarg;
			break;
                case 'n':
                        //specifies the public key file (default: rsa.pub)
                        prub_file = optarg;
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

        if (isHelp == true) {
                printf("SYNOPSIS\n");
                printf("Encrypts data using the RSA alogrithm\n\n");

                 printf("USAGE\n");
                 printf("./encrypt [OPTIONS]\n\n");

                printf("OPTIONS\n");
                printf("-h Print Program Synopsis/Usage\n");
                printf("-v enables Verbose Output\n");
                printf("-i infile specifies the input file (default: stdin)\n");
                printf("-o specifies the output file (default: stdout)\n");
                printf("-n pvfile Public Key File(default: rsa.pub)\n ")
        }

        //INITIALIZE VARS
        mpz_t n, e, s, user;
        mpz_inits(n, e, s, user, NULL);

        //Open the private key file
	char username[300];
	//Open the public key file
        FILE *pubfile = fopen(pub_file, "r");

        //Read the public key from the opened public key file
        rsa_read_pub(n, e, s, username ,pubfile);

        //Verbose
        if (isVerbose == true) {

        }

	//Verify Signature
	mpz_set_str(user, username, 62);
	rsa_verify(user, s, e, n);

        //Decrypt file
        FILE *infile = fopen(in_file, "w");
        FILE *outfile = fopen(out_file, "w");
        rsa_encrypt_file(infile, outfile, n, e);

        //Close file and clear
        fclose(pubfile);
        //randstate_clear();
        mpz_clears(n, e, s, user,  NULL);
        return 0;
}
