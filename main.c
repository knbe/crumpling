#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "vector.h"
#include "pseudo.h"

#define D 2
#define d 3
#define PI 3.141592653589

#include "lattice.h"
#include "write.h"

const int L = 12;
#define N (L*L)

const double J = 1.0;

const double a_0 = (sqrt(2));
const double theta_deg = 60;
const double theta = ((theta_deg / 180) * M_PI);

const double c = 0.1 * a_0; 

const int N_uc = ((L-1)*(L-1));
const int N_tr = (2*N_uc);
const int N_tethers = (3 * N_uc + 2*(L-1));

void initialise_pl_lattice(vector *vtxs, triangle *triangles) {
	double xo_L_inc = (a_0 * cos(theta)); 
	double yo_L_inc = (a_0 * sin(theta));
	double xo = 0; 
	double yo = 0;

	int n = 0;
	for (int j = 0; j < L; j++) {
		for (int i = 0; i < L; i++) {
			vtxs[n].coordinate[0] = xo + a_0 * i;
			vtxs[n].coordinate[1] = yo;
			vtxs[n].coordinate[2] = 0;
			n++;
		}
		xo += xo_L_inc;
		yo += yo_L_inc;
	}

	n = 0;
	int t = 0;
	for (int j = 0; j < L; j++) {
		for (int i = 0; i < L; i++) {
			triangles[t].number = t;
			triangles[t].r0 = vtxs[n];
			triangles[t].r1 = vtxs[n+1];
			triangles[t].r2 = vtxs[n+L];
			t++;
			triangles[t].number = t;
			triangles[t].r0 = vtxs[n+1];
			triangles[t].r1 = vtxs[n+L];
			triangles[t].r2 = vtxs[n+L+1];
			t++;
			n++;
		}
		n++;
	}
}

void gen_sinusoidal_membrane(vector *vtxs, triangle *triangles) {
	int n = 0;
	for (int j = 0; j < L; j++) {

//		double jL = (double)j / (double)L;
//		printf("%f, ", j);
//		printf("%f, ", jL);
//		printf("%f, ", jL * 2 * PI);
//		printf("%f\n", sin(jL * 2 * PI));

		for (int i = 0; i < L; i++) {
			double jL = (double)j / (double)L;
			vtxs[n].coordinate[2] += sin(jL * 2 * PI) * -.5 + 7;
			//printf("%f\n", vtxs[n].coordinate[2]);
			n++;
		}
	}
}

void update_triangles_coords(vector *vtxs, triangle *triangles) {
	int n = 0;
	int t = 0;
	for (int j = 0; j < L; j++) {
		for (int i = 0; i < L; i++) {
			triangles[t].number = t;
			triangles[t].r0 = vtxs[n];
			triangles[t].r1 = vtxs[n+1];
			triangles[t].r2 = vtxs[n+L];
			t++;
			triangles[t].number = t;
			triangles[t].r0 = vtxs[n+1];
			triangles[t].r1 = vtxs[n+L];
			triangles[t].r2 = vtxs[n+L+1];
			t++;
			n++;
		}
		n++;
	}
}

void c_hamiltonian(int N_itr, int itr, vector *vtxs, triangle *triangles) {
	double H_tot = 0;
	for (int t = 0; t < N_tr; t++) {
		double tthr01 = vector_mag(
				vector_subt(
					triangles[t].r0, triangles[t].r1
					)
				);
		//printf("%f\n", tthr01);

		double tthr02 = vector_mag(
				vector_subt(
					triangles[t].r0, triangles[t].r2
					)
				);

		double tthr12 = vector_mag(
				vector_subt(
					triangles[t].r1, triangles[t].r2
					)
				);

		double H = J * (tthr01 + tthr02 + tthr12);

		H_tot += H;
	}

	write_H(N_itr, itr, H_tot);
}

int main() {
	srand(time(NULL));
	vector *vtxs = new_vector_array(N, d);
	//unitcell *unitcells;
	triangle *triangles = new_triangle_array(N_tr);
	initialize_output_files(N, L, N_tr);

	initialise_pl_lattice(vtxs, triangles);

	//gen_sinusoidal_membrane(vtxs, triangles);

	int N_itr = 10000;

	for (int itr = 0; itr < N_itr; itr++) {
		c_hamiltonian(N_itr, itr, vtxs, triangles);
		int rdnvert = rdn_int(0, N);
		vector r_incr = new_vector(d);
		for (int j = 0; j < d; j++)
			r_incr.coordinate[j] = pmsign() * rdn_dbl() * c;
		vtxs[rdnvert] = vector_add(vtxs[rdnvert], r_incr);
	}

	update_triangles_coords(vtxs, triangles);
	write_system_state(N, N_tr, vtxs, triangles);
}
