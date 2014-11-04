/*
 * camara.c
 *
 *  Created on: 21/10/2014
 *      Author: aitor
 */

#include <stdlib.h>
#include "variablesGlobales.h"
#include "definicion.h"

struct 	camara * cam = NULL;
float	nearVal = 0, farVal = 0;
float	factor_zoom = 1.0f;

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

void rotarCamara() {

	// Modificamos pmira y/o v_up, sin modificar la posición
	// Calcular eje de giro -> x_cam(calcularla) dir_mira x v_up
	// 						-> v_up
	//						-> dir_mira
}
