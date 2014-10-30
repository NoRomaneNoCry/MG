#include "o_objet.h"
#include "t_geometrie.h"

/**
 * Calcule le point de la courbe correspondant à la valeur u 
 * Quadruplet * quad : les points de contrôle
 * int nbOfQuad : le nombre de points de contrôle
 * double u : la valeur de u
 * return : le point de contrôle de la courbe pour la valeur u
 */
Quadruplet computePoint(Quadruplet* quad, int nbOfQuad, double u);

/**
 * Calcule tous les points de la courbe
 * Quadruplet * quad : les points de contrôle
 * int nbOfQuad : le nombre de points de contrôle
 * int pt_number : le nombre de points sur la courbe
 * return : l'ensemble des points de la courbe
 */
Table_quadruplet computeAllPoints(Quadruplet* quad, int nbOfQuad, int pt_number);

/**
 * Reparametre la courbe sur l'intervalle [uMin; uMax]
 * Quadruplet * quad : les points de contrôle avant le reparametrage
 * int nbOfQuad : le nombre de points de contrôle
 * double uMin : la borne inférieure de l'intervalle de reparametrage
 * double uMax : la borne supérieure de l'intervalle de reparametrage
 * return : les points de contrôle pour la courbe reparametrée
 */
Table_quadruplet changeParameters(Quadruplet* quad, int nbOfQuad, double uMin, 
		double uMax);

/**
 * Reparametre la courbe sur l'intervalle [0; u]
 * Quadruplet * old_quads : les points de contrôle avant le reparametrage
 * Quadruplet * new_quads : les points de contrôle après le reparametrage
 * int nbOfQuads : le nombre de points de contrôle
 * double u : la borne supérieure de l'intervalle de reparametrage
 */
void changeControlPointsKeepFirstPart(Quadruplet * old_quads, Quadruplet * new_quads,
		int nbOfQuad, double u);

/**
 * Reparametre la courbe sur l'intervalle [u; 1]
 * Quadruplet * old_quads : les points de contrôle avant le reparametrage
 * Quadruplet * new_quads : les points de contrôle après le reparametrage
 * int nbOfQuads : le nombre de points de contrôle
 * double u : la borne inférieure de l'intervalle de reparametrage
 */ 
void changeControlPointsKeepSecondPart(Quadruplet * old_quads, Quadruplet * new_quads,
		int nbOfQuad, double u);
