#ifndef WRITE_H
#define WRITE_H

void initialize_output_files(int N, int L, int N_tr) {
	FILE *vertexData = fopen("./data/vertexdata.csv", "w"); 
	FILE *triangleData = fopen("./data/triangledata.csv", "w");
	FILE *HData = fopen("./data/HData.csv", "w");

	FILE *faceData = fopen("./data/faces.txt", "w");
	int t = 1; 
	int n = 1; 
	for (int j = 1; j < (L); j++) {
		for (int i = 1; i < (L); i++) {
			fprintf(faceData, "%d, %d, %d\n", n, n+1, n+L);
			t++;
			fprintf(faceData, "%d, %d, %d\n", n+1, n+L, n+L+1);
			t++;
			n++;
		}
		n++;
	}
	fclose(faceData);
	fclose(vertexData); 
	fclose(triangleData); 
	//fclose(timeData); 
	//fclose(metaData); 	
}

void write_H(int N_itr, int itr, double H) {
	FILE *HData = fopen("./data/HData.csv", "a");
	fprintf(HData, "%d, %f\n", itr, H);
	fclose(HData);

}

void write_system_state(int N, int N_tr, vector *vtxs, triangle *triangles) {
	FILE *vertexData = fopen("./data/vertexdata.csv", "a");
	FILE *triangleData = fopen("./data/triangledata.csv", "a");

	for (int n = 0; n < N; n++) {
		fprintf(vertexData, "%f, %f, %f\n",
				vtxs[n].coordinate[0], 
				vtxs[n].coordinate[1], 
				vtxs[n].coordinate[2]
				); 
	}

	for (int n = 0; n < N_tr; n++) {
		fprintf(triangleData, "%f, %f, %f, %f, %f, %f, %f, %f, %f\n",
				triangles[n].r0.coordinate[0], 
				triangles[n].r0.coordinate[1], 
				triangles[n].r0.coordinate[2],
				triangles[n].r1.coordinate[0], 
				triangles[n].r1.coordinate[1], 
				triangles[n].r1.coordinate[2],
				triangles[n].r2.coordinate[0], 
				triangles[n].r2.coordinate[1], 
				triangles[n].r2.coordinate[2]
				); 
	}

	fclose(vertexData);
	fclose(triangleData);
}

#endif
