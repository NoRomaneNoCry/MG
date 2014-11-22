#include "o_objet.h"
#include "t_geometrie.h"

/**
 * Calcule les points de la courbe Nurbs
 * Table_quadruplet controlPoints : tableau des points de contrôle
 * int ptNumber : nombre de points sur la courbe
 * int degree : degré de la courbe
 * Table_flottant nodalVector : verteur nodal pour le calcul de la courbe
 */
Table_quadruplet computeAllPointsNurbs(Table_quadruplet controlPoints, int ptNumber,
	int degree, Table_flottant nodalVector);

/**
 * Calcule le points de la courbe correspondant à la valeur u
 */
Quadruplet computePointNurbs(Table_quadruplet controlPoints, double u, int degree,
	Table_flottant nodalVector);

/**
 * Calcule le vecteur nodal qui permettra de calculer la courbe Nurbs
 * int n : le nombre de points de contrôle moins 1
 * int k : l'ordre de la courbe Nurbs
 */
Table_flottant computeNodalVector(int n, int k);