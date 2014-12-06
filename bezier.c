#include "bezier.h"

Quadruplet computePoint(Quadruplet* quad,int nbOfQuad, double u) {
    
    int i, j;
    Quadruplet coords;
    Quadruplet** mat;

    ALLOUER(mat, nbOfQuad);
    for(i=0;i<nbOfQuad;i++)
        ALLOUER(mat[i], nbOfQuad);

    for(i=0; i<nbOfQuad; i++) {
        mat[0][i].x = quad[i].x * quad[i].h;
        mat[0][i].y = quad[i].y * quad[i].h;
        mat[0][i].z = quad[i].z * quad[i].h;
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
    coords.h = mat[nbOfQuad-1][0].h;

    for(i=0;i<nbOfQuad;i++)
        free(mat[i]);
    free(mat);

    return coords;
}

Table_quadruplet computeAllPoints(Quadruplet* quad, int nbOfQuad, int pt_number) {
    
    int i;
    double step = 1.f / (pt_number - 1);
   
    Table_quadruplet tab;
    tab.nb = pt_number;
    ALLOUER(tab.table, pt_number);

    for(i = 0; i < pt_number; i++) {
        tab.table[i] = computePoint(quad, nbOfQuad, i*step);
    }

    return tab;
}

Table_quadruplet changeParameters(Quadruplet* old_quads, int nbOfQuad, double uMin, 
        double uMax) {

    Table_quadruplet tab;
    tab.nb = nbOfQuad;

    Quadruplet * temp;
    ALLOUER(temp, nbOfQuad);

    changeControlPointsKeepFirstPart(old_quads, temp, nbOfQuad, uMax);
    changeControlPointsKeepSecondPart(temp, temp, nbOfQuad, uMin/uMax);

    tab.table = temp;
    
    return tab;
}

void changeControlPointsKeepFirstPart(Quadruplet * old_quads, Quadruplet * new_quads,
        int nbOfQuad, double u) {

    int i, j;
    Quadruplet * temp;
    ALLOUER(temp, nbOfQuad);

    for(i = 0; i < nbOfQuad; i++) {
        temp[i].x = old_quads[i].x * old_quads[i].h;
        temp[i].y = old_quads[i].y * old_quads[i].h;
        temp[i].z = old_quads[i].z * old_quads[i].h;
        temp[i].h = old_quads[i].h;
    }

    new_quads[0].x = temp[0].x / temp[0].h;
    new_quads[0].y = temp[0].y / temp[0].h;
    new_quads[0].z = temp[0].z / temp[0].h;
    new_quads[0].h = temp[0].h ;

    for(i = 1; i < nbOfQuad; i++) {
        for(j = 0; j < nbOfQuad - i; j++) {
            temp[j].x = (u * temp[j+1].x) + ((1-u) * temp[j].x);
            temp[j].y = (u * temp[j+1].y) + ((1-u) * temp[j].y);
            temp[j].z = (u * temp[j+1].z) + ((1-u) * temp[j].z);
            temp[j].h = (u * temp[j+1].h) + ((1-u) * temp[j].h);
        }

        new_quads[i].x = temp[0].x / temp[0].h;
        new_quads[i].y = temp[0].y / temp[0].h;
        new_quads[i].z = temp[0].z / temp[0].h;
        new_quads[i].h = temp[0].h ;
    }

    free(temp);
}

void changeControlPointsKeepSecondPart(Quadruplet * old_quads, Quadruplet * new_quads,
        int nbOfQuad, double u) {

    int i, j;
    Quadruplet * temp;
    ALLOUER(temp, nbOfQuad);

    for(i = 0; i < nbOfQuad; i++) {
        temp[i].x = old_quads[i].x * old_quads[i].h;
        temp[i].y = old_quads[i].y * old_quads[i].h;
        temp[i].z = old_quads[i].z * old_quads[i].h;
        temp[i].h = old_quads[i].h ;
    }

    for(i = 1; i < nbOfQuad; i++) {
        for(j = 0; j < nbOfQuad - i; j++) {
            temp[j].x = (u * temp[j+1].x) + ((1-u) * temp[j].x);
            temp[j].y = (u * temp[j+1].y) + ((1-u) * temp[j].y);
            temp[j].z = (u * temp[j+1].z) + ((1-u) * temp[j].z);
            temp[j].h = (u * temp[j+1].h) + ((1-u) * temp[j].h);
        }
    }

    for(i = 0; i < nbOfQuad; i++) {
        new_quads[i].x = temp[i].x / temp[i].h;
        new_quads[i].y = temp[i].y / temp[i].h;
        new_quads[i].z = temp[i].z / temp[i].h;
        new_quads[i].h = temp[i].h ;
    }

    free(temp);
}
