#include <GL/gl.h>
#include "o_objet.h"
#include "t_geometrie.h"

#include "bezier.h"

struct bezier {

	Table_triplet curvePoints;
	Table_quadruplet controlPoints;
	int pt_number;
	Booleen showControlPoints;

	double uMin;
	double uMax;
};

static void drawBezier(struct bezier * b)
{
	int i;

	glBegin(GL_LINES);
	for(i = 0; i < b->curvePoints.nb - 1; i++) {
		glVertex3f(b->curvePoints.table[i].x, b->curvePoints.table[i].y, 
					b->curvePoints.table[i].z);
		glVertex3f(b->curvePoints.table[i+1].x, b->curvePoints.table[i+1].y, 
					b->curvePoints.table[i+1].z);
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
}

static void changement(struct bezier * b)
{
	if(!(UN_CHAMP_CHANGE(b) || CREATION(b)))
		return;

	if( CREATION(b) || CHAMP_CHANGE(b, pt_number) || 
		CHAMP_CHANGE(b, controlPoints)) {

		free(b->curvePoints.table);
		b->curvePoints = computeAllPoints(b->controlPoints.table, 
											b->controlPoints.nb, b->pt_number);

	}
	else if(((CHAMP_CHANGE(b, uMin) && (b->uMin >= 0) && (b->uMin <= 1))
			 || (CHAMP_CHANGE(b, uMax) && (b->uMax >=0) && (b->uMax <= 1))) 
			&& (b->uMin < b->uMax) ) {

		free(b->curvePoints.table);
		b->curvePoints = changeParametersAndCompute(b->controlPoints.table,
													b->controlPoints.nb, b->pt_number,
													b->uMin, b->uMax);
	}
}

CLASSE(CourbeBezier, struct bezier,

	CHAMP(pt_number, LABEL("Nombre de points") L_entier 
			Edite Sauve DEFAUT("20") )
	CHAMP(showControlPoints, LABEL("Afficher points contrôle") L_booleen
			Edite Sauve DEFAUT("1") )
	CHAMP(uMin, LABEL("Borne min") L_flottant
			Edite Sauve DEFAUT("0") )
	CHAMP(uMax, LABEL("Borne max") L_flottant
			Edite Sauve DEFAUT("1") )
	CHAMP(controlPoints, LABEL("Points de contrôle") L_table_point P_table_quadruplet
			Edite Extrait Obligatoire Sauve)
	CHAMP(curvePoints, L_table_point P_table_triplet
			Sauve)

	CHAMP_VIRTUEL(L_affiche_gl(drawBezier))
	CHANGEMENT(changement)

	MENU("Exemples_MG/Bezier")
	EVENEMENT("Ctrl+BE");

	)