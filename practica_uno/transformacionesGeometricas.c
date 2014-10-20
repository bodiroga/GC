/*
 * transformacionesGeometricas.c
 *
 *  Created on: 20/10/2014
 *      Author: aitor
 */

#include <GL/glut.h>
#include "definicion.h"
#include "variablesGlobales.h"

void escalar(float r) {

	glLoadMatrixf(nodo_actual->matriz);
	glScalef(r, r, r);
	glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);

}

void trasladar(float x, float y, float z) {

//	float tx, ty, tz, factor_x, factor_y, factor_z;
//	tx = x*factor_x;
//	ty = y*factor_y;
//	tz = z*factor_z;
//	factor_x = (max_x - min_x)*0.05f;
//	factor_y = (max_y - min_y)*0.05f;
//	factor_z = (max_z - min_z)*0.05f;
	glLoadMatrixf(nodo_actual->matriz);
	glTranslatef(x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);

}

void rotar(float ang, float x, float y, float z) {

	glLoadMatrixf(nodo_actual->matriz);
	glRotatef(ang, x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);

}

void reset() {

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);

}
