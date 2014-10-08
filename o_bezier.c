#include <GL/gl.h>
#include "o_objet.h"
#include "t_geometrie.h"

#include "bezier.h"

struct bezier {

	Table_triplet curvePoints;
	Table_quadruplet controlPoints;
	int pt_number;

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

	glBegin(GL_LINE_STRIP); // trace n-1 lignes pour n points
	for(i = 0; i < b->controlPoints.nb; i++) {
		glVertex3f(b->controlPoints.table[i].x, b->controlPoints.table[i].y,
					b->controlPoints.table[i].z);
	}
	glEnd();
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
}

CLASSE(CourbeBezier, struct bezier,

	CHAMP(pt_number, LABEL("Nombre de points") L_entier 
			Edite Sauve DEFAUT("10") )
	CHAMP(controlPoints, LABEL("Points de contrôle") L_table_point P_table_quadruplet
			Edite Extrait Obligatoire Sauve)
	CHAMP(curvePoints, L_table_point P_table_triplet
			Sauve)

	CHAMP_VIRTUEL(L_affiche_gl(drawBezier))
	CHANGEMENT(changement)

	MENU("Exemples_MG/Bezier")
	EVENEMENT("Ctrl+BE");

	)