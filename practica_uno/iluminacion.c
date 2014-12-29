/*
 * iluminacion.c
 *
 *  Created on: 24/11/2014
 *      Author: aitor
 */

#include <GL/glut.h>
#include "definicion.h"
#include "variablesGlobales.h"
#include <math.h>

int n_material = 1;

struct MATERIAL oro = {{0.24725, 0.1995, 0.0745}, {0.75164, 0.60648, 0.22648}, {0.628281, 0.555802, 0.366065}};
struct MATERIAL plata = {{0.19225, 0.19225, 0.19225}, {0.50754, 0.50754, 0.50754}, {0.508273, 0.50827, 0.508273}};
struct MATERIAL bronce = {{0.2125, 0.1275, 0.054}, {0.714, 0.4284, 0.18144}, {0.393548, 0.271906, 0.166721}};
struct MATERIAL rubi = {{0.1745, 0.01175, 0.01175}, {0.61424, 0.04136, 0.04136}, {0.727811, 0.626959, 0.626959}};
struct MATERIAL esmeralda = {{0.0215, 0.1745, 0.0215}, {0.07568, 0.61424, 0.07568}, {0.633, 0.727811, 0.633}};

//struct MATERIAL materiales[5] = {oro, plata, bronce, rubi, esmeralda};

void cambiarMaterial() {

	if (n_material >= 5)
		n_material = 1;
	else
		n_material++;

	nodo_actual->n_material = n_material;

}

// case 'm':
//		cambiar_material
//		nodo->n_material++;

// GL_LIGHT()
// luz_ambiente
// case '1':
// 		factor_luz dentro de [0,1]

// glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambiente)

// Definir luces
// luz0.amb->{0.2,0.2,0.2,1}
// glLight(    , AMB, { })

// Encender/Apagar
// glEnable(GL...0)
// glDisale(Gl...0)

// Interruptor
// int interruptor[8]
// case 1:
//		interruptor[1] = 1 - interruptor[1]


