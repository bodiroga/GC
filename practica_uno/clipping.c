/*
 * clipping.c
 *
 *  Created on: 04/10/2014
 *      Author: aitor
 */
#include <GL/glut.h>
#include "definicion.h"
#include "variablesGlobales.h"

float min_x = 0, min_y = 0, min_z = 0;
float max_x = 0, max_y = 0, max_z = 0;


// Funcion que cambia el viewport y las variables ALTO y ANCHO cuando modificamos el
// tamaño de la ventana
void redimensionar(int w, int h) {

	glViewport( 0, 0, w, h);
	ANCHO=w;
	ALTO=h;

}

// Funcion que recibe un objeto como parámetro y actualiza los valores de min_x,...
void actualizar_medidas_escena(OBJETO * objeto) {

	if (objeto->min.x < min_x) min_x = objeto->min.x;
	if (objeto->min.y < min_y) min_y = objeto->min.y;
	if (objeto->min.z < min_z) min_z = objeto->min.z;
	if (objeto->max.x > max_x) max_x = objeto->max.x;
	if (objeto->max.y > max_y) max_y = objeto->max.y;
	if (objeto->max.z > max_z) max_z = objeto->max.z;

}

// Función que ajusta el tamaño del recorte (clipping) a las medidas definidas en
// min_x, min_y, min_z, max_x, max_y, max_z
void clipping() {

	float left, right, top, bottom, near, far, near_cam, far_cam, tan_alpha, tan_beta;

	left = min_x;
	right = max_x;
	bottom = min_y;
	top = max_y;
	near = min_z;
	far = max_z;

	tan_alpha = (top-bottom)/(right-left);
	tan_beta = (ALTO*1.0)/(ANCHO*1.0);

	if(tan_beta < tan_alpha) {
		left *= tan_alpha/tan_beta;
		right *= tan_alpha/tan_beta;
	} else {
		bottom *= tan_beta/tan_alpha;
		top *= tan_beta/tan_alpha;
	}

	glMatrixMode(GL_PROJECTION);	// Cambiamos a Proyection para calcular la proyeccion
	glLoadIdentity();
	if (MODO == 0) {
		glOrtho(left, right, bottom, top, near, far);
	} else {
		glFrustum(left, right, bottom, top, near_cam, far_cam);
	}
	glMatrixMode(GL_MODELVIEW);		// Volvemos a modelview

}
