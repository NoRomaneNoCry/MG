#include <GL/gl.h>
#include "o_objet.h"
#include "t_geometrie.h"

#include "surface_bezier.h"

struct bezier_surface {

	Grille_quadruplet surfacePoints;
	Grille_quadruplet controlPoints;
	int uPtNumber;
	int vPtNumber;
	Booleen showControlPoints;
};

static void drawBezierSurface(struct bezier_surface * s)
{
	int i, j;

	for(i = 0; i < s->surfacePoints.nb_lignes; i++) {
		glBegin(GL_LINE_STRIP);
		for(j = 0; j < s->surfacePoints.nb_colonnes; j++) {
			glVertex3f(s->surfacePoints.grille[i][j].x,
						s->surfacePoints.grille[i][j].y,
						s->surfacePoints.grille[i][j].z);
		}
		glEnd();
	}

	for(i = 0; i < s->surfacePoints.nb_colonnes; i++) {
		glBegin(GL_LINE_STRIP);
		for(j = 0; j < s->surfacePoints.nb_lignes; j++) {
			glVertex3f(s->surfacePoints.grille[j][i].x,
						s->surfacePoints.grille[j][i].y,
						s->surfacePoints.grille[j][i].z);
		}
		glEnd();
	}

	if(s->showControlPoints) {
		for(i = 0; i < s->controlPoints.nb_lignes; i++) {
			glBegin(GL_LINE_STRIP);
			for(j = 0; j < s->controlPoints.nb_colonnes; j++) {
				glVertex3f(s->controlPoints.grille[i][j].x,
							s->controlPoints.grille[i][j].y,
							s->controlPoints.grille[i][j].z);
			}
			glEnd();
		}

		for(i = 0; i < s->controlPoints.nb_colonnes; i++) {
			glBegin(GL_LINE_STRIP);
			for(j = 0; j < s->controlPoints.nb_lignes; j++) {
				glVertex3f(s->controlPoints.grille[j][i].x,
							s->controlPoints.grille[j][i].y,
							s->controlPoints.grille[j][i].z);
			}
			glEnd();
		}
	}
}

static void changement(struct bezier_surface * s)
{
	if(!(UN_CHAMP_CHANGE(s) || CREATION(s)))
		return;

	if(CREATION(s) || CHAMP_CHANGE(s, controlPoints)
		|| CHAMP_CHANGE(s, uPtNumber) || CHAMP_CHANGE(s, vPtNumber)) {

		int i;
		for(i = 0; i < s->surfacePoints.nb_lignes; i++)
			free(s->surfacePoints.grille[i]);
		free(s->surfacePoints.grille);

		s->surfacePoints = computeAllSurfacePoints(s->controlPoints, s->uPtNumber, 
			s->vPtNumber);
	}
}

CLASSE(SurfaceBezier, struct bezier_surface,

	CHAMP(uPtNumber, LABEL("Nombre de points selon u") L_entier
			Edite Sauve DEFAUT("20") )
	CHAMP(vPtNumber, LABEL("Nombre de points selon v") L_entier
			Edite Sauve DEFAUT("20") )
	CHAMP(showControlPoints, LABEL("Afficher les points de contrôle") L_booleen
			Edite Sauve DEFAUT("1") )
	CHAMP(controlPoints, LABEL("Points de contrôle") L_grille_point P_grille_quadruplet
			Edite Extrait Obligatoire Sauve)
	CHAMP(surfacePoints, L_grille_point P_grille_triplet
			Sauve)


	CHAMP_VIRTUEL(L_affiche_gl(drawBezierSurface))
	CHANGEMENT(changement)

	MENU("Exemples_MG/Surface de Bezier")
	EVENEMENT("Ctrl+SB");

	)