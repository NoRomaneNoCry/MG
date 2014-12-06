#include <math.h>
#include "u_xt_interface.h"
#include "t_geometrie.h"

#define ZERO 1E-08

Grille_flottant duplique_Grille_flottant(Grille_flottant *original);
Table_flottant duplique_Table_flottant(Table_flottant *original);
void traite_pivot_max(Grille_flottant  *A,Table_flottant  *f, int colonne);
int resolution_systeme_lineaire(Grille_flottant  *A, Table_flottant  *f, 
	Table_flottant  *x);
