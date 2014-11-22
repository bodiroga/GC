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

	glLoadMatrixf(nodo_actual->matriz);
	glTranslatef(x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);

}

void rotarLocal(float ang, float x, float y, float z) {

	glLoadMatrixf(nodo_actual->matriz);
	glRotatef(ang, x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);

}

void rotarGlobal(float ang, float x, float y, float z) {

	glLoadIdentity();
	glRotatef(ang, x, y, z);
	glMultMatrixf(nodo_actual->matriz);
	glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);

}

void reset() {

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);

}
