#include "o_objet.h"
#include "t_geometrie.h"

Triplet computePoint(Quadruplet* quad,int nbOfQuad, double u);
Table_triplet computeAllPoints(Quadruplet* quad, int nbOfQuad, int pt_number);
Table_triplet changeParametersAndCompute(Quadruplet* quad, int nbOfQuad, 
										int pt_number, double uMin, double uMax);
void changeControlPointsKeepSecondPart(Quadruplet * quad, int nbOfQuad, double u);
void changeControlPointsKeepFirstPart(Quadruplet * quad, int nbOfQuad, double u);
