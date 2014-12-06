#include "o_objet.h"
#include "t_geometrie.h"

#include <math.h>

#include "sys_lin.h"

/**
 * Calcule, à l'aide de la méthode des moindres carrées, les points de contrôle
 * pernettant d'approximer les points passés en paramètre et retourne ces points
 * de contrôle.
 */
Table_quadruplet least_squares_approximation(Table_triplet points,
	Booleen uniformConf);

/**
 * Multiplie deux matrices carrées A et B et retourne le résultat
 * int size : la taille des matrices (les deux matrices doivent avoir la même
 * taille)
 */
double ** matrix_matrix_mult(double ** A, double ** B, int size);

/**
 * Multiplie une matrice carrées avec un vecteur et retoure le résultat
 * int size : la taille de la matrice et du vecteur
 */
double * matrix_vector_mult(double ** B, double * V, int size);

/**
 * Retourne la transposée de la matrice
 */
double ** transposedMatrix(double ** matrix, int size);

/**
 * Calcule la valeur des u correspondantes au points à approximer. Ces u permettrons
 * de remplir la matrice qui sera utilisée pour les moindres carrés
 */
Table_flottant steps_computation(Table_triplet points, Booleen uniformConf);

/**
 * Distance de deux points en 3D
 */
double distance(Triplet pointA, Triplet pointB);

/**
 * Retourne la valeur du polynome de Bernstein de degré n pour la partition i et
 * la valeur u
 */
double bernsteinPolynomial(int i, int n, double u);

/**
 * Retourne la factorielle de x
 */
int fact(int x);

/**
 * Découpe les coordonnées d'un vecteur de triplets en 3 vecteurs x, y, z. Ces
 * trois vecteurs doivent être alloués au préalable.
 */
void split_x_y_z(Table_triplet points, double * x, double * y, double * z);
