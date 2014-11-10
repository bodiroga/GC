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

	// 1º Calcular matriz de rotacion
	//		3 opciones: - cambia vup si rotamos sobre z
	//				 	- cambia dir_mira si rotamos sobre y
	//					- cambia vup y dir_mira si rotamos sobre x
	//
	// vup = G * vup
	// dir_mira = G * dir_mira
	//
	// Caso rotacion x: eje = xc = vup x dir_mira
	// Caso rotacion y: eje = vup
	// Caso rotacion z: eje = dir_mira
	//
	// Identity
	// glRotate( ang, eje.x, eje.y, eje.z)
	// glFloatv( GL_MODELVIEW_MATRIX)
	//
	// Tenemos que crear una funcion que nos haga la multiplicacion vectorial y el producto matriz por vector

	// mult_matriz_por_vector(float matriz[16], vector3d vector) {
	//
	// }
	// 2º Rotar la cámara con la matriz de rotacion

	// No cambiamos la posicion de la camara !!

	float G[16];
	vector3d eje;
	float ang;
	glGetFloatv(GL_MODELVIEW_MATRIX, G);

	if (xyz == 1) {
		cam->vup = mult_matriz_por_vector(G, cam->vup);
		eje = cam->vdir;
		ang = 5.0f;
	} else if (xyz == -1) {
		cam->vup = mult_matriz_por_vector(G, cam->vup);
		eje = cam->vdir;
		ang = -5.0f;
	} else if (xyz == 10) {
		cam->vdir = mult_matriz_por_vector(G, cam->vdir);
		eje = cam->vup;
		ang = 5.0f;
	} else if (xyz == -10) {
		cam->vdir = mult_matriz_por_vector(G, cam->vdir);
		eje = cam->vup;
		ang = -5.0f;
	} else if (xyz == 100) {
		cam->vup = mult_matriz_por_vector(G, cam->vup);
		cam->vdir = mult_matriz_por_vector(G, cam->vdir);
		eje = mult_vectorial(cam->vup, cam->vdir);
		ang = 5.0f;
	} else if (xyz == -100) {
		cam->vup = mult_matriz_por_vector(G, cam->vup);
		cam->vdir = mult_matriz_por_vector(G, cam->vdir);
		eje = mult_vectorial(cam->vup, cam->vdir);
		ang = -5.0f;
	}

	glLoadIdentity();
	glRotate(ang, eje.x, eje.y, eje.z);
	glFloatv( GL_MODELVIEW_MATRIX);

	// Modificamos pmira y/o v_up, sin modificar la posición
	// Calcular eje de giro -> x_cam(calcularla) dir_mira x v_up
	// 						-> v_up
	//						-> dir_mira
}


