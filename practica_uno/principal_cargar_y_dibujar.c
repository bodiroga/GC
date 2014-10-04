#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <GL/glut.h>
#include "definicion.h"

int lecturaObjeto(char * , OBJETO * );
void dibuja(void);
void dibuja_un_objeto(OBJETO *);
void actualizar_medidas_escena(OBJETO *);
void clipping();
void cargaObjeto();
void seleccionaObjeto();
void cambiaColor();

struct NODO * primer_nodo = NULL ;
struct NODO * nodo_actual = NULL;
struct NODO * nodo_aux = NULL;

static float	LOCAL_RED = 0.5f;
static float	LOCAL_GREEN = 0.5f;
static float	LOCAL_BLUE = 0.5f;
static float	SELECTED_RED = 1.0f;
static float	SELECTED_GREEN = 0.0f;
static float	SELECTED_BLUE = 0.0f;
static int		ANCHO = 500, ALTO = 500, color = 0;
float			min_x, min_y, min_z, max_x, max_y, max_z;

static void teclado (unsigned char key, int x, int y)
{
	// This function will be called whenever the user pushes one key
	switch(key) {
		case 'c': 
			cargaObjeto();
			break;
		case 'm':
			cambiaColor();
			break;
		case 9: // <TAB>
			seleccionaObjeto();
			break;
		case 27:  // <ESC>
			exit(0);
			break;
		default:
			printf("opcion incorrecta: %d %c\n", key, key );
	}
	
	glutPostRedisplay();
}

void redimensionar(int w, int h) {

	glViewport( 0, 0, w, h); 
	ANCHO=w;
	ALTO=h;

}

void actualizar_medidas_escena(OBJETO * objeto) {

	if (objeto->min.x < min_x) min_x = objeto->min.x;
	if (objeto->min.y < min_y) min_y = objeto->min.y;
	if (objeto->min.z < min_z) min_z = objeto->min.z;
	if (objeto->max.x > max_x) max_x = objeto->max.x;
	if (objeto->max.y > max_y) max_y = objeto->max.y;
	if (objeto->max.z > max_z) max_z = objeto->max.z;

}

void clipping() {

	float left, right, top, bottom, near, far, tan_alpha, tan_beta;

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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(left, right, bottom, top, near, far);

}

void dibuja_un_objeto(OBJETO * mi_objeto) {

	int i = 0;
	int j = 0;
	int numVertice = 0;
	float a, b, c;

	clipping();
	
	if ((nodo_actual != NULL) && (mi_objeto == nodo_actual->objeto))
		glColor3f(SELECTED_RED, SELECTED_GREEN, SELECTED_BLUE);
	else
		glColor3f(LOCAL_RED, LOCAL_GREEN, LOCAL_BLUE);

	for (i = 0; i < mi_objeto->numeroCaras; i++) {
		glBegin(GL_LINE_LOOP);
		for (j = 0; j < mi_objeto->tablaCaras[i].numeroVertices; j++) {
			numVertice = mi_objeto->tablaCaras[i].tablaVertices[j];	
			a = mi_objeto->tablaVertices[numVertice].coord.x;
			b = mi_objeto->tablaVertices[numVertice].coord.y;
			c = mi_objeto->tablaVertices[numVertice].coord.z;
			glVertex3f(a, b, c);
		}
		glEnd();
	}
	glFlush();
}

void dibuja(void) {

	glClear( GL_COLOR_BUFFER_BIT );
	if (primer_nodo != NULL) {
		nodo_aux = primer_nodo;
		do {
			dibuja_un_objeto(nodo_aux->objeto);
		} while ((nodo_aux = nodo_aux->siguiente) != NULL);
	}
	glFlush();
}

void cargaObjeto() {

	char ruta[150]= "./Objetos";
	char nombreFigura[20];
	struct OBJETO * objeto_aux;

	printf("Cargar figura (*.obj): ");
	scanf("%s", nombreFigura);
	fflush(stdin);
	strcat(ruta, nombreFigura);
	
	objeto_aux = (OBJETO *)malloc(sizeof(OBJETO));

	if (lecturaObjeto(ruta, objeto_aux) == 0) {
		printf("Objeto leido\n");

		// Reservamos memoria para el nodo_aux, que ser� el que haga de puente
		nodo_aux = (NODO *)malloc(sizeof(NODO));
		
		nodo_aux->objeto = objeto_aux;
		nodo_aux->siguiente = primer_nodo;

		primer_nodo = nodo_aux;

		actualizar_medidas_escena(objeto_aux);

	} else {
		objeto_aux = NULL;
		printf("Objeto NO leido\n");
	}
}

void seleccionaObjeto() {

	if ((nodo_actual == NULL) || (nodo_actual->siguiente == NULL))
		nodo_actual = primer_nodo;
	else
		nodo_actual = nodo_actual->siguiente;
	
}

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

int main(int argc, char** argv) {

	printf("Este programa carga un objeto \n");
	printf("y lo dibuja en pantalla \n");
	printf("Pulsar <c> para cargar un objeto\n");
	printf("Pulsar <ESC> para finalizar\n");
		
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_RGB );
	glutInitWindowSize ( ANCHO, ALTO );
	glutInitWindowPosition ( 0, 0 );
	glutCreateWindow( "Cargo y Dibujo UN objeto" );

	glutDisplayFunc( dibuja );
	glutKeyboardFunc( teclado );
	glutReshapeFunc(redimensionar);

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glutMainLoop();

	return 0;   
}
