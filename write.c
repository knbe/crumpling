#include <stdio.h>
#include <stdlib.h>

#define d 3

#include "vector.h"
#include "lattice.h"
#include "write.h"

void initialize_output_files() {
	FILE *vertexData = fopen("./data/vertexdata.csv", "w"); 
	FILE *triangleData = fopen("./data/triangledata.csv", "w");
	//FILE *timeData = fopen("./data/sim_timedata.csv", "w"); 
	//FILE *metaData = fopen("./data/sim_metadata.txt", "w"); 

#if 0
	fprintf(metaData, 
		"%s\n%s\n%f\n%f\n%d\n%d\n%d\n%d\n", 
		system_name(), 
		simulation.initSpecifier,
	       	simulation.timeStep, 
		simulation.totalRunTime,	
		manifold.N, 
		manifold.K_H, 
		manifold.K_S, 
		manifold.K_I);

	for (int n = 0; n < manifold.N; n++)
	{
		fprintf(metaData, "%f\n", manifold.particle[n].mass); 
	}
#endif

	fclose(vertexData); 
	fclose(triangleData); 
	//fclose(timeData); 
	//fclose(metaData); 	
}

void write_system_state(vector *vtxs, triangle *triangles) {
#if 0
	FILE *timeData = fopen("./data/sim_timedata.csv", "a"); 
	FILE *cartStateData = fopen("./data/sim_data_cartesian.csv", "a"); 

	fprintf(timeData, "%f\n", t * simulation.timeStep);

	for (int n = 0; n < manifold.N; n++)
	{
		fprintf(cartStateData, "%f, %f, %f\n%f, %f, %f\n", 
			manifold.particle[n].position.coordinate[0], 
			manifold.particle[n].position.coordinate[1], 
			manifold.particle[n].position.coordinate[2],
			manifold.particle[n].velocity.coordinate[0], 
			manifold.particle[n].velocity.coordinate[1], 
			manifold.particle[n].velocity.coordinate[2]);
	}	

	fclose(timeData); 
	fclose(cartStateData); 
#endif
}
