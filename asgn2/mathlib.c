#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mathlib.h"

double Exp(double x) {
	double trm = 1.0;
	double sum = trm;
	double k = 1;
	while(trm > EPSILON) {
		trm = trm * (fabs(x) / k);
		sum += trm;	
		k += 1;
	}

	if (x > 0) {
		return sum;
	} else {
		return (1/sum);
	}
}

double Sin(double x) {
	double s = 1.0;
	double v = x;
	double t = x;
 	double k = 3.0;

	while(fabs(t) > EPSILON) {
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
	double t = 1.0;
	double k = 2.0;

	while(fabs(t) > EPSILON) {
		t = t*((x*x) / ((k-1)*k));
		s = -s;
		v += s*t;
		k += 2.0;
	}
	
	return v;

}

double Sqrt(double x) {
	double z = 0.0;
	double y = 1.0;

	while(fabs(y-z) > EPSILON) {
		z = y;
		y = 0.5 * (z + (x / z));
	}

	return y;
}

double Log(double x) {
	double y = 1.0;
	double p = Exp(y);
	while(fabs(p-x) > EPSILON) {
		y = y + x / p - 1;
		p = Exp(y);
	}

	return y;
}
