#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "definicion.h"
#include "ruta.h"
#include "variablesGlobales.h"

int lecturaObjeto(char * , OBJETO * );
void dibujaEjes();
void redimensionar(int w, int h);
void actualizar_medidas_escena(OBJETO *);
void clipping();
void cargaObjeto();
void seleccionaObjeto();
void cambiaColor();
void cambiarMaterial();
void escalar(float r);
void trasladar(float x, float y, float z);
void rotarLocal(float ang, float x, float y, float z);
void rotarGlobal(float ang, float x, float y, float z);
void reset();
void cambiarModo();
void cargarCamara();
void trasladarCamara(float x, float y, float z);
void zoomCamara(float factor);
void rotarCamaraTripode(int xyz);
void rotarCamaraSatelite(int xy);
void resetCamara();
void normal_caras(OBJETO *);


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
int		MODO = 0;

static void teclado (unsigned char key, int x, int y) {
	// This function will be called whenever the user pushes one key
	switch(key) {
		/////  Cargar objeto  /////
		case 'c': 
			cargaObjeto();
			break;
		/////  Cambiar color objeto seleccionado  /////
		case 'v':
			cambiaColor();
			break;
		//////  Trasladar objeto  /////
		case 'a':
			trasladar(-1.0f,0.0f,0.0f);
			break;
		case 'd':
			trasladar(1.0f,0.0f,0.0f);
			break;
		case 'w':
			trasladar(0.0f,1.0f,0.0f);
			break;
		case 's':
			trasladar(0.0f,-1.0f,0.0f);
			break;
		case 'q':
			trasladar(0.0f,0.0f,1.0f);
			break;
		case 'e':
			trasladar(0.0f,0.0f,-1.0f);
			break;
		/////  Rotar objeto en local  //////
		case 'f':
			rotarLocal(5.0f,0.0f,-1.0f,0.0f);
			break;
		case 'h':
			rotarLocal(5.0f,0.0f,1.0f,0.0f);
			break;
		case 't':
			rotarLocal(5.0f,-1.0f,0.0f,0.0f);
			break;
		case 'g':
			rotarLocal(5.0f,1.0f,0.0f,0.0f);
			break;
		case 'r':
			rotarLocal(5.0f,0.0f,0.0f,1.0f);
			break;
		case 'y':
			rotarLocal(5.0f,0.0f,0.0f,-1.0f);
			break;
		//////  Rotar objeto en global  //////
		case 'F':
			rotarGlobal(5.0f,0.0f,-1.0f,0.0f);
			break;
		case 'H':
			rotarGlobal(5.0f,0.0f,1.0f,0.0f);
			break;
		case 'T':
			rotarGlobal(5.0f,-1.0f,0.0f,0.0f);
			break;
		case 'G':
			rotarGlobal(5.0f,1.0f,0.0f,0.0f);
			break;
		case 'R':
			rotarGlobal(5.0f,0.0f,0.0f,1.0f);
			break;
		case 'Y':
			rotarGlobal(5.0f,0.0f,0.0f,-1.0f);
			break;
		/////  Trasladar camara  //////
		case 'A':
			trasladarCamara(-1.0f,0.0f,0.0f);
			break;
		case 'D':
			trasladarCamara(1.0f,0.0f,0.0f);
			break;
		case 'W':
			trasladarCamara(0.0f,1.0f,0.0f);
			break;
		case 'S':
			trasladarCamara(0.0f,-1.0f,0.0f);
			break;
		case 'Q':
			trasladarCamara(0.0f,0.0f,1.0f);
			break;
		case 'E':
			trasladarCamara(0.0f,0.0f,-1.0f);
			break;
		/////  Zoom camara  /////
		case 'z':
			zoomCamara(0.9f);
			break;
		case 'Z':
			zoomCamara(1.1f);
			break;
		/////  Rotar camara tripode  /////
		case 'j':
			rotarCamaraTripode(10);
			break;
		case 'l':
			rotarCamaraTripode(-10);
			break;
		case 'i':
			rotarCamaraTripode(-100);
			break;
		case 'k':
			rotarCamaraTripode(100);
			break;
		case 'u':
			rotarCamaraTripode(1);
			break;
		case 'o':
			rotarCamaraTripode(-1);
			break;
		/////  Rotar camara órbita  /////
		case 'J':
			rotarCamaraSatelite(-1);
			break;
		case 'L':
			rotarCamaraSatelite(1);
			break;
		case 'I':
			rotarCamaraSatelite(10);
			break;
		case 'K':
			rotarCamaraSatelite(-10);
			break;
		/////  Resetear camara  /////
		case 'n':
			resetCamara();
			break;
		/////  Resetear objeto  /////
		case '0':
			reset();
			break;
		/////  Cambiar modo de proyección  /////
		case 'p':
			cambiarModo();
			break;
		/////  Zoom objeto  /////
		case 43: // <+>
			escalar(1.1f);
			break;
		case 45: // <->
			escalar(0.9f);
			break;
		/////  Cambiar material  /////
		case 'm':
			cambiarMaterial();
			break;
		/////  Iluminación  /////
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		/////  Cambiar objeto seleccionado  /////
		case 9: // <TAB>
			seleccionaObjeto();
			break;
		/////  Salir del programa  /////
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
	
	if ((nodo_actual != NULL) && (mi_objeto == nodo_actual->objeto)) {
		dibujaEjes();
		glColor3f(SELECTED_RED, SELECTED_GREEN, SELECTED_BLUE);
	} else
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

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_COLOR);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHT0);
	glClear( GL_COLOR_BUFFER_BIT);
	if (primer_nodo != NULL) {
		nodo_aux = primer_nodo;
		do {
			if (MODO == 0) {
				glLoadMatrixf(nodo_aux->matriz);
			} else if (MODO == 1) {
				glLoadIdentity();
				gluLookAt(cam->posicion.x, cam->posicion.y, cam->posicion.z,
						cam->pmira.x, cam->pmira.y, cam->pmira.z,
						cam->vup.x, cam->vup.y, cam->vup.z);
				glMultMatrixf(nodo_aux->matriz);
			}
			dibuja_un_objeto(nodo_aux->objeto);
		} while ((nodo_aux = nodo_aux->siguiente) != NULL);
	}
	glFlush();
}

void dibujaEjes(void) {

	float valor_ejes = nodo_actual->objeto->max.x;
	if (valor_ejes > nodo_actual->objeto->max.y) valor_ejes = nodo_actual->objeto->max.y;
	if (valor_ejes > nodo_actual->objeto->max.z) valor_ejes = nodo_actual->objeto->max.z;

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(valor_ejes, 0, 0);
	glVertex3f(0, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, valor_ejes, 0);
	glVertex3f(0, 0, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, valor_ejes);
	glVertex3f(0, 0, 0);
	glEnd();
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

		if (nodo_actual == NULL)
			nodo_actual = primer_nodo;

		actualizar_medidas_escena(objeto_aux);
		normal_caras(objeto_aux);

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

void cambiarModo() {

	if (MODO == 0)
		MODO = 1;
	else
		MODO = 0;
}


int main(int argc, char** argv) {

	printf("Este programa carga varios objetos \n");
	printf("y los dibuja en pantalla \n");
	printf("Pulsar <c> para cargar un objeto\n");
	printf("Pulsar <m> para cambiar el color del objeto seleccionado\n");
	printf("Pulsar <TAB> para seleccionar un objeto\n");
	printf("Pulsar <ESC> para finalizar\n");

	cargaObjeto();
	cargarCamara();

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
