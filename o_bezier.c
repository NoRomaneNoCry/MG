#include <GL/gl.h>
#include "o_objet.h"
#include "t_geometrie.h"

#include "bezier.h"

struct bezier {

	Table_quadruplet curvePoints;
	Table_quadruplet controlPoints;
	Table_quadruplet reconfiguredCurvePoints;
	Table_quadruplet reconfiguredControlPoints;
	int curvePtNumber;
	int reconfiguredCurvePtNumber;
	Booleen showControlPoints;
	Booleen showReconfiguredControlPoints;

	double uMin;
	double uMax;
};

static void drawBezier(struct bezier * b)
{
	int i;

	glBegin(GL_LINE_STRIP);
	for(i = 0; i < b->curvePoints.nb; i++) {
		glVertex3f(b->curvePoints.table[i].x, b->curvePoints.table[i].y, 
					b->curvePoints.table[i].z);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for(i = 0; i < b->reconfiguredCurvePoints.nb; i++) {
		glVertex3f(b->reconfiguredCurvePoints.table[i].x, b->reconfiguredCurvePoints.table[i].y,
					b->reconfiguredCurvePoints.table[i].z);
	}
	glEnd();

	if(b->showControlPoints) {
		glBegin(GL_LINE_STRIP); // trace n-1 lignes pour n points
		for(i = 0; i < b->controlPoints.nb; i++) {
			glVertex3f(b->controlPoints.table[i].x, b->controlPoints.table[i].y,
						b->controlPoints.table[i].z);
		}
		glEnd();
	}

	if(b->showReconfiguredControlPoints) {
		glBegin(GL_LINE_STRIP);
		for(i = 0; i < b->reconfiguredControlPoints.nb; i++) {
			glVertex3f(b->reconfiguredControlPoints.table[i].x,
						b->reconfiguredControlPoints.table[i].y,
						b->reconfiguredControlPoints.table[i].z);
		}
		glEnd();
	}

}

static void changement(struct bezier * b)
{
	if(!(UN_CHAMP_CHANGE(b) || CREATION(b)))
		return;

	if( CREATION(b) || CHAMP_CHANGE(b, controlPoints)) {

		free(b->curvePoints.table);
		b->curvePoints = computeAllPoints(b->controlPoints.table, 
				b->controlPoints.nb, b->curvePtNumber);
		free(b->reconfiguredControlPoints.table);
		b->reconfiguredControlPoints = changeParameters(b->controlPoints.table,
				b->controlPoints.nb, b->uMin, b->uMax);
		free(b->reconfiguredCurvePoints.table);
		b->reconfiguredCurvePoints = computeAllPoints(b->reconfiguredControlPoints.table,
				b->reconfiguredControlPoints.nb, b->reconfiguredCurvePtNumber);
		
	}
	else if(CHAMP_CHANGE(b, curvePtNumber)) {

		free(b->curvePoints.table);
		b->curvePoints = computeAllPoints(b->controlPoints.table, 
				b->controlPoints.nb, b->curvePtNumber);
	}
	else if(((CHAMP_CHANGE(b, uMin) && (b->uMin >= 0) && (b->uMin <= 1))
			 || (CHAMP_CHANGE(b, uMax) && (b->uMax >=0) && (b->uMax <= 1))) 
			&& (b->uMin < b->uMax) ) {

		free(b->reconfiguredControlPoints.table);
		b->reconfiguredControlPoints = changeParameters(b->controlPoints.table,
				b->controlPoints.nb, b->uMin, b->uMax);
		free(b->reconfiguredCurvePoints.table);
		b->reconfiguredCurvePoints = computeAllPoints(b->reconfiguredControlPoints.table,
				b->reconfiguredControlPoints.nb, b->reconfiguredCurvePtNumber);
	}
	else if(CHAMP_CHANGE(b, reconfiguredCurvePtNumber)) {

		free(b->reconfiguredCurvePoints.table);
		b->reconfiguredCurvePoints = computeAllPoints(b->reconfiguredControlPoints.table,
				b->reconfiguredControlPoints.nb, b->reconfiguredCurvePtNumber);
	}
}

CLASSE(CourbeBezier, struct bezier,

	CHAMP(curvePtNumber, LABEL("Nombre de points de la courbe") L_entier 
			Edite Sauve DEFAUT("20") )
	CHAMP(showControlPoints, LABEL("Afficher points contrôle courbe") L_booleen
			Edite Sauve DEFAUT("1") )
	CHAMP(controlPoints, LABEL("Points de contrôle courbe") L_table_point P_table_quadruplet
			Edite Extrait Obligatoire Sauve)
	CHAMP(curvePoints, L_table_point P_table_triplet
			Sauve)
	CHAMP(uMin, LABEL("Borne min reparamétrage") L_flottant
			Edite Sauve DEFAUT("0") )
	CHAMP(uMax, LABEL("Borne max reparamétrage") L_flottant
			Edite Sauve DEFAUT("1") )
	CHAMP(reconfiguredCurvePtNumber, LABEL("Nombre de points de la courbe reparamétrée") L_entier
			Edite Sauve DEFAUT("20") )
	CHAMP(showReconfiguredControlPoints, LABEL("Afficher points contrôle courbe reparamétrée") L_booleen
			Edite Sauve DEFAUT("1") )
		CHAMP(reconfiguredControlPoints, LABEL("Points de contrôle courbe reparamétrée") L_table_point P_table_quadruplet
			Affiche Sauve)
	CHAMP(reconfiguredCurvePoints, L_table_point P_table_triplet
			Sauve)

	CHAMP_VIRTUEL(L_affiche_gl(drawBezier))
	CHANGEMENT(changement)

	MENU("Exemples_MG/Courbe de Bezier")
	EVENEMENT("Ctrl+BE");

	)