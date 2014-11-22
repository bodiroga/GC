/*
 * camara.c
 *
 *  Created on: 21/10/2014
 *      Author: aitor
 */

#include <stdlib.h>
#include "variablesGlobales.h"
#include "definicion.h"
#include <GL/glut.h>

struct 	camara * cam = NULL;
float	nearVal = 0, farVal = 0;
float	factor_zoom = 1.0f;


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

void cargarCamara() {

	float fondo = max_z - min_z;
	if (cam == NULL)
		cam = (camara *)malloc(sizeof(camara));
	cam->posicion.x = 0;
	cam->posicion.y = 0;
	cam->posicion.z = 2*(fondo);
	cam->pmira.x = 0;
	cam->pmira.y = 0;
	cam->pmira.z = 0;
	cam->vup.x = 0;
	cam->vup.y = 1;
	cam->vup.z = 0;
	cam->vdir.x = cam->posicion.x - cam->pmira.x;
	cam->vdir.y = cam->posicion.y - cam->pmira.y;
	cam->vdir.z = cam->posicion.z - cam->pmira.z;
	nearVal = fondo;
	farVal = 10*fondo;

}

void trasladarCamara(float x, float y, float z) {

	cam->posicion.x += x;
	cam->posicion.y += y;
	cam->posicion.z += z;

	cam->pmira.x += x;
	cam->pmira.y += y;
	cam->pmira.z += z;

}

void zoomCamara(float factor) {

	factor_zoom *= factor;

}

void rotarCamaraTripode(int xyz) {

	float G[16];
	vector3d eje;
	float ang;

	if ((xyz == 1) || (xyz == -1)) // Rotación eje z
		eje = cam->vdir;
	else if ((xyz == 10) || (xyz == -10)) // Rotación eje y
		eje = cam->vup;
	else if ((xyz == 100) || (xyz == -100)) // Rotación eje x
		eje = mult_vectorial(cam->vdir, cam->vup);

	if (xyz > 0) // Rotación positiva
		ang = 5.0f;
	else // Rotación negativa
		ang = -5.0f;

	glLoadIdentity();
	glRotatef(ang, eje.x, eje.y, eje.z);

	glGetFloatv(GL_MODELVIEW_MATRIX, G);

	if ((xyz == 1) || (xyz == -1)) { // Rotación eje z
		cam->vup = mult_matriz_por_vector(G, cam->vup);
	} else if ((xyz == 10) || (xyz == -10)) { // Rotación eje y
		cam->vdir = mult_matriz_por_vector(G, cam->vdir);
	} else if ((xyz == 100) || (xyz == -100)) { // Rotación eje x
		cam->vup = mult_matriz_por_vector(G, cam->vup);
		cam->vdir = mult_matriz_por_vector(G, cam->vdir);
	}

	cam->pmira.x = cam->posicion.x - cam->vdir.x;
	cam->pmira.y = cam->posicion.y - cam->vdir.y;
	cam->pmira.z = cam->posicion.z - cam->vdir.z;



}

void rotarCamaraSatelite(int xy) {

	float G[16];
	vector3d eje;
	float ang;

	if ((xy == 1) || (xy == -1)) // Rotación eje y
		eje = cam->vup;
	else if ((xy == 10) || (xy == -10)) // Rotación eje x
		eje = mult_vectorial(cam->vdir, cam->vup);

	if (xy > 0) // Rotación positiva
		ang = 5.0f;
	else // Rotación negativa
		ang = -5.0f;

	glLoadIdentity();
	glRotatef(ang, eje.x, eje.y, eje.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, G);

	if ((xy == 1) || (xy == -1)) { // Rotación eje y
		cam->vdir = mult_matriz_por_vector(G, cam->vdir);
	} else if ((xy == 10) || (xy == -10)) { // Rotación eje x
		cam->vup = mult_matriz_por_vector(G, cam->vup);
		cam->vdir = mult_matriz_por_vector(G, cam->vdir);
	}

	cam->posicion.x = cam->pmira.x - cam->vdir.x;
	cam->posicion.y = cam->pmira.y - cam->vdir.y;
	cam->posicion.z = cam->pmira.z - cam->vdir.z;

}

void resetCamara() {

	cargarCamara();

}


