/*
 * camara.c
 *
 *  Created on: 21/10/2014
 *      Author: aitor
 */

#include <stdlib.h>
#include "variablesGlobales.h"
#include "definicion.h"

struct camara * cam = NULL;

void cargarCamara() {

	cam = (camara *)malloc(sizeof(camara));
	cam->posicion.x = 0;
	cam->posicion.y = 0;
	cam->posicion.z = -1.5*(max_z-min_z);
	cam->pmira.x = 0;
	cam->pmira.y = 0;
	cam->pmira.z = 0;
	cam->vup.x = 0;
	cam->vup.y = 1;
	cam->vup.z = 0;
	near_cam = max_z - min_z;
	far_cam = 2*(max_z - min_z);

}
