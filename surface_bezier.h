#include "o_objet.h"
#include "t_geometrie.h"

#include "bezier.h"

/**
 * Calcule tous les points de la surface 
 * Grille_quadruplet controlPoints : grille de points de contrôle
 * int uPtNumber : nombre de points sur la courbe selon u
 * int vPtNumber : nombre de points sur la courbe selon v
 */
Grille_quadruplet computeAllSurfacePoints(Grille_quadruplet controlPoints, int uPtNumber,
		int vPtNumber);

