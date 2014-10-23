#include "o_objet.h"
#include "t_geometrie.h"

Triplet computePoint(Quadruplet* quad, int nbOfQuad, double u);
Table_triplet computeAllPoints(Quadruplet* quad, int nbOfQuad, int pt_number);
Table_quadruplet changeParameters(Quadruplet* quad, int nbOfQuad, double uMin, 
		double uMax);
void changeControlPointsKeepFirstPart(Quadruplet * old_quads, Quadruplet * new_quads,
		int nbOfQuad, double u);
void changeControlPointsKeepSecondPart(Quadruplet * old_quads, Quadruplet * new_quads,
		int nbOfQuad, double u);
