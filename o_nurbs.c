#include <GL/gl.h>
#include "o_objet.h"
#include "t_geometrie.h"

#include "nurbs.h"

struct nurbs {

	Table_flottant nodalVector;
	Table_quadruplet curvePoints;
	Table_quadruplet controlPoints;
	int curvePtNumber;
	int curveDegree;
	Booleen showControlPoints;	
};

static void drawNurbs(struct nurbs * n)
{
	int i;

	glBegin(GL_LINE_STRIP);
	for(i = 0; i < n->curvePoints.nb; i++) {
		glVertex3f(n->curvePoints.table[i].x, n->curvePoints.table[i].y,
					n->curvePoints.table[i].z);
	}
	glEnd();

	if(n->showControlPoints) {
		glBegin(GL_LINE_STRIP);
		for(i = 0; i < n->controlPoints.nb; i++) {
			glVertex3f(n->controlPoints.table[i].x, n->controlPoints.table[i].y,
						n->controlPoints.table[i].z);
		}
		glEnd();
	}
}

static void changement(struct nurbs * n)
{
	if(!(UN_CHAMP_CHANGE(n) || CREATION(n)))
		return;

	if(CREATION(n) || CHAMP_CHANGE(n, controlPoints) || CHAMP_CHANGE(n, curveDegree)) {

		free(n->nodalVector.table);
		n->nodalVector = computeNodalVector(n->controlPoints.nb - 1, n->curveDegree + 1);
		free(n->curvePoints.table);
		n->curvePoints = computeAllPointsNurbs(n->controlPoints, n->curvePtNumber,
			n->curveDegree, n->nodalVector);
	}
	else if(CHAMP_CHANGE(n, nodalVector) || CHAMP_CHANGE(n, curvePtNumber)) {

		free(n->curvePoints.table);
		n->curvePoints = computeAllPointsNurbs(n->controlPoints, n->curvePtNumber,
			n->curveDegree, n->nodalVector);
	}
}

CLASSE(CourbeNurbs, struct nurbs,

	CHAMP(curvePtNumber, LABEL("Nombre de points de la courbe") L_entier
			Edite Sauve DEFAUT("20") )
	CHAMP(showControlPoints, LABEL("Afficher les points de contrôle") L_booleen
			Edite Sauve DEFAUT("1") )
	CHAMP(curveDegree, LABEL("Degré de la courbe") L_entier
			Edite Sauve DEFAUT("2") )
	CHAMP(nodalVector, LABEL("Vecteur nodal") L_table_flottant P_table_flottant
			Edite Sauve)
	CHAMP(controlPoints, LABEL("Points de contrôle") L_table_point P_table_quadruplet
			Edite Extrait Obligatoire Sauve)
	CHAMP(curvePoints, L_table_point P_table_quadruplet
			Sauve)


	CHAMP_VIRTUEL(L_affiche_gl(drawNurbs))
	CHANGEMENT(changement)

	MENU("Exemples_MG/Courbe Nurbs")
	EVENEMENT("Ctrl+CN");

	)