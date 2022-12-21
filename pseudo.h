#ifndef PSEUDO_H
#define PSEUDO_H

double rdn() {
	return((rand() % 10000) / 10000.0);
}

int rdn_int(int lb, int ub) {
	return((rand() % ((ub-1) - lb + 1)) + lb);
}

double rdn_dbl() {
	return (double)rand()/RAND_MAX;
}

int pmsign() {
	double x = (double)rand()/RAND_MAX;
	int sign;
	if (x < 0.5)
		sign = -1; 
	else
		sign = 1;
	return sign;
}


#endif
