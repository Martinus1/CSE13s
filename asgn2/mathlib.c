#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

#define EPSILON 1e-14

double Exp(double x) {
	double  trm = 1.0;
	double  sum = trm;
	double k = 1;
	while(trm > EPSILON) {
		trm *= abs(x) / k;
		sum += trm;	
		k += 1;
	}

	if x > 0 {
		return sum;
	} else {
		return (1/sum);
	}
}

double Sin(double x) {
	double s = 1.0;
	double v = x;
	double t = x;
 	double k = 3.0:

	while(abs(t) > EPSILON) {
		t = t*((x*x) / ((k-1)*k));
		s = -s;
		v += s*t;
		k += 2.0;
	}

	return v;
}

double Cos(double x) {
	double s = 1.0;
	double v = 1.0;
	double t = x;
	double k = 1.0;

	while(abs(t) > EPSILON) {
		t = t*((t*(x*x) )/((k-1)*k));
		s = -s;
		v += s*t;
		k += 2.0
	}
	
	return v;

}

double Sqrt(double x) {
	double z = 0.0;
	double y = 1.0;

	while(abs(y-z) > EPSILON) {
		z = y;
		y = 0.5 * (z + (x / z));
	}

	return y;
}

double Log(double x) {
	double y = 1.0;
	double p = Exp(y);
	while(abs(p-x) > EPSILON) {
		y = (y+x)/(p-1);
		p = Exp(y);
	}

	return y;
}
