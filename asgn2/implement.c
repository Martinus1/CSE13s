#include <stdio.h>
#include "mathlib.h"
#include "functions.h"
#include <stdlib.h>
#include <math.h>


double main(int argc, char **argv) {

	uint32_t n = 0;
	double high = 0.0;
	double low = 0.0;
	double (*function)(double) = a;

	while((opt = getopt(argc,argv, "abcdefghij:n:p:q:H:")) != 1) {
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
				fprintf("Synopsis of the program");
				break;
			default:
				fprintf(stderr, "error/n");
				return 1;
		}
	}

	
	if (n % 2) == 0 {
		integrate(&function, low, hight, n); 
	} else {
		fprintf("error");
	}

}


double integrate(double (*f)(double x), double a, double b, uint32_t n) {
	double step = (a-b) / n;
	double res = 0;

	for (int i = 0; i <= n; i += 1) {
		x = a + (i * step);
		fx = (*f)(x);
		if i == 0 or i == n {
			res += fx;
		} else  if (i % 2) != 0 {
			res += 4*fx;
		} else {
			res += 2*fx;
		}
		
	}

	res = (h/3) * res;

	return res;
}





