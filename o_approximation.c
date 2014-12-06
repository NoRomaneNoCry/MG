#include <GL/gl.h>
#include "o_objet.h"
#include "t_geometrie.h"

#include "approximation.h"
#include "bezier.h"

struct approximation {

	Table_triplet pointsAapproximer;
	Table_quadruplet controlPoints;
	Table_quadruplet curve;
	Booleen uniformConfiguration;
	Booleen showControlPoints;
	int curvePtNb;
};

static void drawApproximation(struct approximation * a)
{
	int i;

	glBegin(GL_LINE_STRIP);
	for(i = 0; i < a->curve.nb; i++) {
		glVertex3f(a->curve.table[i].x, a->curve.table[i].y, a->curve.table[i].z);
	}
	glEnd();
	if(a->showControlPoints) {
		glBegin(GL_LINE_STRIP);
		for(i = 0; i < a->controlPoints.nb; i++) {
			glVertex3f(a->controlPoints.table[i].x, a->controlPoints.table[i].y, 
				a->controlPoints.table[i].z);
		}
		glEnd();
	}
	glBegin(GL_POINTS);
	for(i = 0; i < a->pointsAapproximer.nb; i++) {
		glVertex3f(a->pointsAapproximer.table[i].x, a->pointsAapproximer.table[i].y,
			a->pointsAapproximer.table[i].z);
	}
	glEnd();
}

static void changement(struct approximation * a)
{
	if(!(UN_CHAMP_CHANGE(a) || CREATION(a)))
		return;

	if(CREATION(a) || CHAMP_CHANGE(a, pointsAapproximer) 
		|| CHAMP_CHANGE(a, uniformConfiguration)) {

		free(a->controlPoints.table);
		a->controlPoints = least_squares_approximation(a->pointsAapproximer, 
			a->uniformConfiguration);
		free(a->curve.table);
		a->curve = computeAllPoints(a->controlPoints.table, a->controlPoints.nb, 
			a->curvePtNb);
	}
	else if(CHAMP_CHANGE(a, curvePtNb)) {

		free(a->curve.table);
		a->curve = computeAllPoints(a->controlPoints.table, a->controlPoints.nb, 
			a->curvePtNb);
	}
}

CLASSE(approximation, struct approximation,

	CHAMP(pointsAapproximer, LABEL("Points à approximer") L_table_point P_table_triplet
			Edite Extrait Obligatoire Sauve)
	CHAMP(curvePtNb, LABEL("Nombre de points sur la courbe") L_entier
			Edite Sauve DEFAUT("20") )
	CHAMP(uniformConfiguration, LABEL("Configuration uniforme") L_booleen
			Edite Sauve DEFAUT("1") )
	CHAMP(showControlPoints, LABEL("Afficher les points de contrôle") L_booleen
			Edite Sauve DEFAUT("1") )
	CHAMP(curve, L_table_point P_table_quadruplet
			Affiche Sauve)
	CHAMP(controlPoints, L_table_point P_table_quadruplet
			Affiche Sauve)

	CHAMP_VIRTUEL(L_affiche_gl(drawApproximation))
	CHANGEMENT(changement)

	MENU("Exemples_MG/Approximation")
	EVENEMENT("Ctrl+AP");

	)