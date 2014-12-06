#include "approximation.h"

Table_quadruplet least_squares_approximation(Table_triplet points, 
	Booleen uniformConf) {

	int i, j;

	Table_quadruplet res;
	res.nb = points.nb;
	ALLOUER(res.table, points.nb);

	Table_flottant steps = steps_computation(points, uniformConf);

	double ** B;
	ALLOUER(B, points.nb);
	for(i = 0; i < points.nb; i++)
		ALLOUER(B[i], points.nb);

	B[0][0] = B[points.nb - 1][points.nb - 1] = 1;
	for(i = 1; i < points.nb; i++)
		B[0][i] = 0;
	for(i = 0; i < points.nb; i++) { 
		for(j = 1; j < points.nb - 1; j++) {
			B[j][i] = bernsteinPolynomial(i, points.nb - 1, steps.table[j]);
		}
	}
	for(i = 0; i < points.nb - 1; i++)
		B[points.nb - 1][i] = 0;

	double ** BT = transposedMatrix(B, points.nb);

	Grille_flottant Aprime;
	Aprime.nb_lignes = Aprime.nb_colonnes = points.nb;
	Aprime.grille = matrix_matrix_mult(B, BT, points.nb);

	for(i = 0; i < points.nb; i++)
		free(BT[i]);
	free(BT);

	double * pointsX, * pointsY, * pointsZ;
	ALLOUER(pointsX, points.nb);
	ALLOUER(pointsY, points.nb);
	ALLOUER(pointsZ, points.nb);
	split_x_y_z(points, pointsX, pointsY, pointsZ);

	Table_flottant BprimeX, BprimeY, BprimeZ;
	BprimeX.nb = BprimeY.nb = BprimeZ.nb = points.nb;
	BprimeX.table = matrix_vector_mult(B, pointsX, points.nb);
	BprimeY.table = matrix_vector_mult(B, pointsY, points.nb);
	BprimeZ.table = matrix_vector_mult(B, pointsZ, points.nb);

	free(pointsX); free(pointsY); free(pointsZ);
	for(i = 0; i < points.nb; i++)
		free(B[i]);
	free(B);

	Table_flottant resX, resY, resZ;
	resX.nb = resY.nb = resZ.nb = points.nb;
	ALLOUER(resX.table, points.nb);
	ALLOUER(resY.table, points.nb);
	ALLOUER(resZ.table, points.nb);

	resolution_systeme_lineaire(&Aprime, &BprimeX, &resX);
	resolution_systeme_lineaire(&Aprime, &BprimeY, &resY);
	resolution_systeme_lineaire(&Aprime, &BprimeZ, &resZ);

	for(i = 0; i < points.nb; i++) {
		res.table[i].x = resX.table[i];
		res.table[i].y = resY.table[i];
		res.table[i].z = resZ.table[i];
		res.table[i].h = 1;
	}

	free(BprimeX.table); free(BprimeY.table); free(BprimeZ.table);
	free(resX.table); free(resY.table); free(resZ.table);
	for(i = 0; i < Aprime.nb_lignes; i++)
		free(Aprime.grille[i]);
	free(Aprime.grille);

	return res;
}

void split_x_y_z(Table_triplet points, double * x, double * y, double * z) {

	int i;

	for(i = 0; i < points.nb; i++) {
		x[i] = points.table[i].x;
		y[i] = points.table[i].y;
		z[i] = points.table[i].z;
	}
}

double * matrix_vector_mult(double ** B, double * V, int size) {

	int i, j;
  	double s;

  	double * mult;
  	ALLOUER(mult, size);

  	for(j = 0; j < size; j++)
    {
      	s = 0;
      	for(i = 0; i < size; i++)
			s += B[j][i] * V[i];
      	
      	mult[j] = s;
    }

    return mult;
}

double ** matrix_matrix_mult(double ** A, double ** B, int size) {

	int i, j, k;
	double s;

	double ** mult;
	ALLOUER(mult, size);
	for(i = 0; i < size; i++)
		ALLOUER(mult[i], size);

	for(j = 0; j < size; j++) {
    	for(i = 0; i < size; i++) {
			s = 0 ;
			for(k = 0; k < size; k++)
	  			s += A[j][k] * B[k][i];
			
			mult[j][i] = s;
      	}
    }

	return mult;
}

double ** transposedMatrix(double ** matrix, int size) {

	int i, j;

	double ** trans;
	ALLOUER(trans, size);
	for(i = 0; i < size; i++)
		ALLOUER(trans[i], size);

	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			trans[i][j] = matrix[j][i];
		}
	}

	return trans;
}

Table_flottant steps_computation(Table_triplet points, Booleen uniformConf) {

	int i;

	Table_flottant steps;
	steps.nb = points.nb;
	ALLOUER(steps.table, steps.nb);

	if(uniformConf) {
		for(i = 0; i < steps.nb; i++)
			steps.table[i] = i * (1.f / (points.nb - 1));
	}
	else {
		double totalDistance = 0;
		steps.table[0] = 0.f;
		for(i = 1; i < steps.nb; i++) {
			totalDistance += distance(points.table[i-1], points.table[i]);
			steps.table[i] = totalDistance;
		}
		for(i = 1; i < steps.nb; i++)
			steps.table[i] /= totalDistance;
	}

	return steps;
}

double distance(Triplet pointA, Triplet pointB) {

	return sqrt(pow(pointB.x - pointA.x, 2) + pow(pointB.y - pointA.y, 2)
		+ pow(pointB.z - pointA.z, 2));
}

double bernsteinPolynomial(int i, int n, double u) {

	return (fact(n) / (fact(i) * fact(n -i))) * pow(u, i) * pow(1.f - u, n - i);
}

int fact(int x) {

	int res = 1;

	for(; x > 1; --x)
		res *= x;

	return res;
}