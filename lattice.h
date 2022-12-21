#ifndef LATTICE_H
#define LATTICE_H

typedef struct unitcell {
	int number;
	vector r0;
	vector r1;
	vector r2;
} unitcell;

typedef struct triangle {
	int number;
	vector r0;
	vector r1;
	vector r2;
} triangle;

typedef struct tether {
	int number;
	vector r0;
	vector r1;
} tether;

triangle *new_triangle_array(int N_tr) {
	triangle *t1 = malloc(N_tr * sizeof(triangle)); 

	for (int n = 0; n < N_tr; n++)
	{
		t1[n].number = n; 
		t1[n].r0 = new_vector(d);
		t1[n].r1 = new_vector(d);
		t1[n].r2 = new_vector(d);
	}

	return t1; 
}

tether *new_tether_array(int N_tethers) {
}

#endif
