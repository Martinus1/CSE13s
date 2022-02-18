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
    char *priv_file = "rsa.priv";
    char *in_file = "stdin";
    char *out_file = "stdout";
    bool isVerbose = false;
    bool isHelp = false;

    while ((opt = getopt(argc, argv, "i:o:n:vh")) != -1) {
        switch (opt) {
        case 'i':
            //specifies the input file (default: stdin)
            in_file = optarg;
            break;
        case 'o':
            //specifies the output file (default: stdout)
            out_file = optarg;
            break;
        case 'n':
            //specifies the private key file (default: rsa.priv)
            priv_file = optarg;
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

    if (isHelp) {
        printf("SYNOPSIS\n");
        printf("Decrypts data using the RSA decryption alogrithm\n\n");

        printf("USAGE\n");
        printf("./decrypt [OPTIONS]\n\n");

        printf("OPTIONS\n");
        printf("-h Print Program Synopsis/Usage\n");
        printf("-v enables Verbose Output\n");
        printf("-i infile specifies the input file (default: stdin)\n");
        printf("-o specifies the output file (default: stdout)\n");
        printf("-n pvfile Private Key File(default: rsa.priv)\n ");
    }

    //INITIALIZE VARS
    mpz_t n, d, user;
    mpz_inits(n, d, user, NULL);

    //Open the private key file
    FILE *privfile = fopen(priv_file, "r");

    //Read the private key from the opened public key file
    rsa_read_priv(n, d, privfile);

    //Verbose
    if (isVerbose == true) {
    }

    //Decrypt file
    FILE *infile = fopen(in_file, "w");
    FILE *outfile = fopen(out_file, "w");
    rsa_decrypt_file(infile, outfile, n, d);

    //Close file and clear
    fclose(privfile);
    //randstate_clear();
    mpz_clears(n, d, user, NULL);

    return 0;
}
