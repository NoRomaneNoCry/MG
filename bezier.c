#include "bezier.h"

#include "o_objet.h"
#include "t_geometrie.h"

Triplet computePoint(Quadruplet* quad,int nbOfQuad, double u) {
    
    int i, j;
    Triplet coords;
    Quadruplet** mat;

    ALLOUER(mat, nbOfQuad);
    for(i=0;i<nbOfQuad;i++)
        ALLOUER(mat[i], nbOfQuad);

    for(i=0; i<nbOfQuad; i++) {
        mat[0][i].x = quad[i].x;
        mat[0][i].y = quad[i].y;
        mat[0][i].z = quad[i].z;
        mat[0][i].h = quad[i].h;
    }

    for(i=1; i<nbOfQuad;i++) {
        for(j=0; j<nbOfQuad-i;j++) {
            mat[i][j].x = (u * mat[i-1][j+1].x) + ((1-u) * mat[i-1][j].x);
            mat[i][j].y = (u * mat[i-1][j+1].y) + ((1-u) * mat[i-1][j].y);
            mat[i][j].z = (u * mat[i-1][j+1].z) + ((1-u) * mat[i-1][j].z);
            mat[i][j].h = (u * mat[i-1][j+1].h) + ((1-u) * mat[i-1][j].h);
        }
    }   

    coords.x = mat[nbOfQuad-1][0].x / mat[nbOfQuad-1][0].h;
    coords.y = mat[nbOfQuad-1][0].y / mat[nbOfQuad-1][0].h;
    coords.z = mat[nbOfQuad-1][0].z / mat[nbOfQuad-1][0].h;

    for(i=0;i<nbOfQuad;i++)
        free(mat[i]);
    free(mat);

    return coords;
}

Table_triplet computeAllPoints(Quadruplet* quad, int nbOfQuad, int pt_number) {
    
    int i;
    double step = 1.f / (pt_number - 1);

    Table_triplet tab;
    tab.nb = pt_number;
    ALLOUER(tab.table, pt_number);

    for(i = 0; i < pt_number; i++) {
        tab.table[i] = computePoint(quad, nbOfQuad, i*step);
    }

    return tab;
}
