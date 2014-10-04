/*
 * color.c
 *
 *  Created on: 04/10/2014
 *      Author: aitor
 */
#include "variablesGlobales.h"

void cambiaColor() {

	if (color == 7) color = 0; else color++;

	switch (color) {
		case 0: // Rojo
			SELECTED_RED = 1.0f; SELECTED_GREEN = 0.0f; SELECTED_BLUE = 0.0f; break;
		case 1: // Naranja
			SELECTED_RED = 1.0f; SELECTED_GREEN = 0.5f; SELECTED_BLUE = 0.0f; break;
		case 2: // Verde
			SELECTED_RED = 0.0f; SELECTED_GREEN = 1.0f; SELECTED_BLUE = 0.0f; break;
		case 3: // Azul
			SELECTED_RED = 0.0f; SELECTED_GREEN = 0.0f; SELECTED_BLUE = 3.0f; break;
		case 4: // Amarillo
			SELECTED_RED = 1.0f; SELECTED_GREEN = 1.0f; SELECTED_BLUE = 0.0f; break;
		case 5: // Morado
			SELECTED_RED = 1.0f; SELECTED_GREEN = 0.0f; SELECTED_BLUE = 1.0f; break;
		case 6: // Azul claro
			SELECTED_RED = 0.0f; SELECTED_GREEN = 1.0f; SELECTED_BLUE = 1.0f; break;
		case 7: // Blanco
			SELECTED_RED = 1.0f; SELECTED_GREEN = 1.0f; SELECTED_BLUE = 1.0f; break;
		default:  // Rojo
			SELECTED_RED = 1.0f; SELECTED_GREEN = 0.0f; SELECTED_BLUE = 0.0f; break;
	}
}
