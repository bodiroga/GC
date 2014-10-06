#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <GL/glut.h>
#include "definicion.h"
#include "ruta.h"
#include "variablesGlobales.h"

int lecturaObjeto(char * , OBJETO * );
void redimensionar(int w, int h);
void actualizar_medidas_escena(OBJETO *);
void clipping();
void cargaObjeto();
void seleccionaObjeto();
void cambiaColor();
void escalado(float r);

struct NODO * primer_nodo = NULL ;
struct NODO * nodo_actual = NULL;
struct NODO * nodo_aux = NULL;

static float	LOCAL_RED = 0.5f;
static float	LOCAL_GREEN = 0.5f;
static float	LOCAL_BLUE = 0.5f;
float	SELECTED_RED = 1.0f;
float	SELECTED_GREEN = 0.0f;
float	SELECTED_BLUE = 0.0f;
int		ANCHO = 700, ALTO = 800;
int		color = 0;

static void teclado (unsigned char key, int x, int y) {
	// This function will be called whenever the user pushes one key
	switch(key) {
		case 'c': 
			cargaObjeto();
			break;
		case 'm':
			cambiaColor();
			break;
		case 43:
			escalado(1.1f);
			break;
		case 45:
			escalado(0.9f);
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
			glLoadMatrixf(nodo_aux->matriz);
			dibuja_un_objeto(nodo_aux->objeto);
		} while ((nodo_aux = nodo_aux->siguiente) != NULL);
	}
	glFlush();
}

void cargaObjeto() {

	char nombreFigura[20];
	char rutaObjeto[150] = "";
	struct OBJETO * objeto_aux;
	int i = 0;

	printf("Cargar figura (*.obj): ");
	scanf("%s", nombreFigura);
	fflush(stdin);
	strcat(rutaObjeto, ruta);
	strcat(rutaObjeto, nombreFigura);
	
	objeto_aux = (OBJETO *)malloc(sizeof(OBJETO));

	if (lecturaObjeto(rutaObjeto, objeto_aux) == 0) {
		printf("Objeto leido\n");

		// Reservamos memoria para el nodo_aux, que ser� el que haga de puente
		nodo_aux = (NODO *)malloc(sizeof(NODO));
		
		nodo_aux->objeto = objeto_aux;
		nodo_aux->siguiente = primer_nodo;

		for (i = 0; i < 16; i++)
			nodo_aux->matriz[i] = 0;
		for (i = 0; i < 16; i = i+5)
			nodo_aux->matriz[i] = 1;

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

void escalado(float r) {

	if (nodo_actual != NULL) {
		glLoadMatrixf(nodo_actual->matriz);
		glScalef(r, r, r);
		glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);
	}
}

void traslacion(float x, float y, float z) {

	if (nodo_actual != NULL) {
		glLoadMatrixf(nodo_actual->matriz);
		glTranslatef(x, y, z);
		glGetFloatv(GL_MODELVIEW_MATRIX, nodo_actual->matriz);
	}

}


int main(int argc, char** argv) {

	printf("Este programa carga un objeto \n");
	printf("y lo dibuja en pantalla \n");
	printf("Pulsar <c> para cargar un objeto\n");
	printf("Pulsar <m> para cambiar el color del objeto seleccionado\n");
	printf("Pulsar <TAB> para seleccionar un objeto\n");
	printf("Pulsar <ESC> para finalizar\n");
		
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_RGB );
	glutInitWindowSize ( ANCHO, ALTO );
	glutInitWindowPosition ( 0, 0 );
	glutCreateWindow( "Cargo y Dibujo UN objeto" );

	glutDisplayFunc( dibuja );
	glutKeyboardFunc( teclado );
	glutReshapeFunc( redimensionar );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glutMainLoop();

	return 0;   
}
