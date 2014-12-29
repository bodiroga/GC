/*
 * operaciones.c
 *
 *  Created on: 29/12/2014
 *      Author: aitor
 */

#include "definicion.h"
#include <math.h>

vector3d mult_matriz_por_vector(float matriz[16], vector3d vector) {

	vector3d resultado;

	resultado.x = matriz[0]*vector.x + matriz[4]*vector.y + matriz[8]*vector.z;
	resultado.y = matriz[1]*vector.x + matriz[5]*vector.y + matriz[9]*vector.z;
	resultado.z = matriz[2]*vector.x + matriz[6]*vector.y + matriz[10]*vector.z;

	return resultado;

}

vector3d mult_vectorial(vector3d vector1, vector3d vector2) {

	vector3d resultado;

	resultado.x = vector1.y*vector2.z - vector1.z*vector2.y;
	resultado.y = vector1.z*vector2.x - vector1.x*vector2.z;
	resultado.z = vector1.x*vector2.y - vector1.y*vector2.x;

	return resultado;

}

void normal_caras(OBJETO * objeto) {

	int i;
	int indTablaVertices0, indTablaVertices1, indTablaVertices2;
	vector3d v1, v2, vNormal;
	double norma;

	for(i=0; i < objeto->numeroCaras; i++) {

		indTablaVertices0 = objeto->tablaCaras[i].tablaVertices[0];
		indTablaVertices1 = objeto->tablaCaras[i].tablaVertices[1];
		indTablaVertices2 = objeto->tablaCaras[i].tablaVertices[2];

		v1.x = objeto->tablaVertices[indTablaVertices1].coord.x - objeto->tablaVertices[indTablaVertices0].coord.x;
		v1.y = objeto->tablaVertices[indTablaVertices1].coord.y - objeto->tablaVertices[indTablaVertices0].coord.y;
		v1.z = objeto->tablaVertices[indTablaVertices1].coord.z - objeto->tablaVertices[indTablaVertices0].coord.z;

		v2.x = objeto->tablaVertices[indTablaVertices2].coord.x - objeto->tablaVertices[indTablaVertices1].coord.x;
		v2.y = objeto->tablaVertices[indTablaVertices2].coord.y - objeto->tablaVertices[indTablaVertices1].coord.y;
		v2.z = objeto->tablaVertices[indTablaVertices2].coord.z - objeto->tablaVertices[indTablaVertices1].coord.z;

		vNormal = mult_vectorial(v1, v2);

		norma = sqrt(vNormal.x*vNormal.x + vNormal.y*vNormal.y + vNormal.z*vNormal.z);

		vNormal.x = vNormal.x/norma;
		vNormal.y = vNormal.y/norma;
		vNormal.z = vNormal.z/norma;

		objeto->tablaCaras[i].normal = vNormal;
	}

}

void normal_vertices(OBJETO * objeto){

	int i, j;
	double norma;

	for(i=0; i < objeto->numeroVertices; i++) {
		objeto->tablaVertices[i].normal.x = 0;
		objeto->tablaVertices[i].normal.y = 0;
		objeto->tablaVertices[i].normal.z = 0;
	}

	for (i=0; i < objeto->numeroCaras; i++) {
		for (j=0; j < objeto->tablaCaras[i].numeroVertices; j++){
			objeto->tablaVertices[j].normal.x += abs(objeto->tablaCaras[i].normal.x);
			objeto->tablaVertices[j].normal.y += abs(objeto->tablaCaras[i].normal.y);
			objeto->tablaVertices[j].normal.z += abs(objeto->tablaCaras[i].normal.z);
		}
	}

	for (i = 0; i < objeto->numeroVertices; i++){
		norma = sqrt(objeto->tablaVertices[i].normal.x*objeto->tablaVertices[i].normal.x + objeto->tablaVertices[i].normal.y*objeto->tablaVertices[i].normal.y + objeto->tablaVertices[i].normal.z*objeto->tablaVertices[i].normal.z);
		objeto->tablaVertices[i].normal.x = objeto->tablaVertices[i].normal.x / norma;
		objeto->tablaVertices[i].normal.y = objeto->tablaVertices[i].normal.y / norma;
		objeto->tablaVertices[i].normal.z = objeto->tablaVertices[i].normal.z / norma;
	}
}
