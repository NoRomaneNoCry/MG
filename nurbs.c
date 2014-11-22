#include "nurbs.h"

Table_flottant computeNodalVector(int n, int k) {

	int i;
	Table_flottant tab;
	tab.nb = n+k+1;
	ALLOUER(tab.table, n+k+1);

	for(i = 0; i < k; i++)
		tab.table[i] = 0;
	for(i = k; i <= n ; i++)
		tab.table[i] = (i - k + 1.f)/(n - k + 2.f);
	for(i = n+1; i <= n+k; i++)
		tab.table[i] = 1;

	return tab;
}

Quadruplet computePointNurbs(Table_quadruplet controlPoints, double u, int degree,
	Table_flottant nodalVector) {

	Quadruplet coords;
	int i, j, r;
	int k = degree + 1;
	double ui, uikj;
	double coefi, coefi1;

	Quadruplet * temp;
	ALLOUER(temp, controlPoints.nb);

	for(i = 0; i < nodalVector.nb-1; i++) {
		if(u >= nodalVector.table[i] && (u < nodalVector.table[i+1])) {
			r = i;
			break;
		}
	}

	for(i = 0; i < controlPoints.nb; i++) {
		temp[i].x = controlPoints.table[i].x * controlPoints.table[i].h;
		temp[i].y = controlPoints.table[i].y * controlPoints.table[i].h;
		temp[i].z = controlPoints.table[i].z * controlPoints.table[i].h;
		temp[i].h = controlPoints.table[i].h;
	}

	for(j = 1; j <= degree; j++) {		
		for(i = r - k + 1 + j; i <= r; i++) {
			ui = nodalVector.table[i];
			uikj = nodalVector.table[i+k-j];
			coefi = (u - ui) / (uikj - ui);
			coefi1 = (uikj - u) / (uikj - ui);
			temp[i].x = coefi * temp[i].x + coefi1 * temp[i-1].x;
			temp[i].y = coefi * temp[i].y + coefi1 * temp[i-1].y;
			temp[i].z = coefi * temp[i].z + coefi1 * temp[i-1].z;
			temp[i].h = coefi * temp[i].h + coefi1 * temp[i-1].h;
		}
	}

	coords.x = temp[r].x / temp[r].h;
	coords.y = temp[r].y / temp[r].h;
	coords.z = temp[r].z / temp[r].h;
	coords.h = temp[r].h;

	free(temp);
	return coords;
}

Table_quadruplet computeAllPointsNurbs(Table_quadruplet controlPoints, int ptNumber,
	int degree, Table_flottant nodalVector) {

	int i;
	double step = 1.f / (ptNumber - 1);

	Table_quadruplet points;
	points.nb = ptNumber;
	ALLOUER(points.table, ptNumber);

	for(i = 0; i < ptNumber; i++)
		points.table[i] = computePointNurbs(controlPoints, i * step, degree, nodalVector);

	return points;
}
