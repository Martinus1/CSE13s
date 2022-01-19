#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "mathlib.h"
#include "functions.h"


double integrate(double (*f)(double x), double a, double b, uint32_t n);

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Prints the Integral of a function.\n"
        "\n"
        "USAGE\n"
        "   %s [-hn:r:] [-(a-j) function select] [-n partitions num] [-p low] [-q high]  \n"
        "\n"
        "OPTIONS\n"
	"   -(a-j) select function to integrate. \n"
        "   -H display program help and usage.\n"
        "   -n partitions   number of partitions - even.\n"
        "   -p low low integral starting point.\n",
        exec);
}

int main(int argc, char **argv) {

	uint32_t n = 0;
	double high = 0.0;
	double low = 0.0;
	double (*function)(double) = a;

	int opt = 0;
	while((opt = getopt(argc, argv, "abcdefghij:n:p:q:H:")) != -1) {
		switch (opt) {
			case 'a':
				function = a;
				break;
			case 'b':
				function = b;
				break;
			case 'c':
				function = c;
				break;
			case 'd':
				function = d;
				break;
			case 'e':
				function = e;
				break;
			case 'f':
				function = f;
				break;
			case 'g':
				function = g;
				break;
			case 'h':
				function = h;
				break;
			case 'i':
				function = i;
				break;
			case 'j':
				function = j;
				break;
			case 'n':
				n = atoi(optarg);
				break;
			case 'p':
				low = strtod(optarg, NULL);
				break;
			case 'q':
				high = strtod(optarg, NULL);
				break;
			case 'H':
				usage(argv[0]); return EXIT_FAILURE;
			default:
				fprintf(stderr, "error/n");
				return 1;
		}
	}

	
	if (n % 2 == 0) {
		integrate(function, low, high, n); 
	} else {
		fprintf(stderr,"error/n");
		return 1;
	}

}


double integrate(double (*f)(double x), double a, double b, uint32_t n) {
	double step = (a-b) / n;
	double res = 0;

	for (uint32_t i = 0; i <= n; i += 1) {
		double x = a + (i * step);
		double fx = (*f)(x);
		if (i == 0 || i == n) {
			res += fx;
		} else if (i % 2 != 0) {
			res += 4*fx;
		} else {
			res += 2*fx;
		}
		
	}

	res = (b/3) * res;

	return res;
}





