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

void cargarCamara() {

	printf("Los valores de max_z y min_z son: %f y %f\n", max_z, min_z);
	float fondo = max_z - min_z;
	if (cam == NULL)
		cam = (camara *)malloc(sizeof(camara));
	cam->posicion.x = 0;
	cam->posicion.y = 0;
	cam->posicion.z = 1.5*(fondo);
	cam->pmira.x = 0;
	cam->pmira.y = 0;
	cam->pmira.z = 0;
	cam->vup.x = 0;
	cam->vup.y = 1;
	cam->vup.z = 0;
	nearVal = 3*fondo;
	farVal = 5*(fondo);

}
