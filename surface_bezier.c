#include "surface_bezier.h"

Grille_quadruplet computeAllSurfacePoints(Grille_quadruplet controlPoints, int uPtNumber,
		int vPtNumber) {

	int i, j;
	Grille_quadruplet grille;
	Table_quadruplet * pts_temp;
	double stepU = 1.f / (uPtNumber - 1);
	double stepV = 1.f / (vPtNumber - 1);

	// Grille résultat
	grille.nb_lignes = vPtNumber;
	grille.nb_colonnes = uPtNumber;
	ALLOUER(grille.grille, grille.nb_lignes);
	for(i = 0; i < grille.nb_lignes; i++)
		ALLOUER(grille.grille[i], grille.nb_colonnes);

	// Points de contrôle temporaires
	ALLOUER(pts_temp, uPtNumber);
	for(i = 0; i < uPtNumber; i++) {
		pts_temp[i].nb = controlPoints.nb_lignes;
		ALLOUER(pts_temp[i].table, controlPoints.nb_lignes);
	}

	for(i = 0; i < uPtNumber; i++) {
		for(j = 0; j < controlPoints.nb_lignes; j++) {
			pts_temp[i].table[j] = computePoint(controlPoints.grille[j], 
				controlPoints.nb_colonnes, i*stepU);
		}
	}

	for(i = 0; i < vPtNumber; i++) {
		for(j = 0; j < uPtNumber; j++) {
			grille.grille[i][j] = computePoint(pts_temp[j].table, pts_temp[j].nb, 
				i*stepV);
		}
	}
	
	for(i = 0; i < uPtNumber; i++)
		free(pts_temp[i].table);
	free(pts_temp);

	return grille;
}
