
#ifndef DEFINICION_H
#define DEFINICION_H

typedef struct NODO {
				struct OBJETO * objeto;
				struct NODO * siguiente;
				float matriz[16];
				int n_material;
				} NODO;

typedef struct MATERIAL {
				float ambiente[4];
				float difuso[4];
				float especular[4];
				} MATERIAL;

typedef struct {
               double x,y,z;
               } punto3d;

typedef struct {
               double x,y,z;
               } vector3d;

typedef struct {
               double r,g,b;
               } intensidad3;

/****************************************************************/
/****** Definicion de las estructuras de datos ******************/
/****************************************************************/

/*----------------------- VERTICE --------------------------------------*/

typedef struct {
    vector3d normal;
    punto3d coord;      /** coordenadas ,x, y, z **/
    int numeroCaras;    /** cuantas caras tiene **/
} vertice;

/*----------------------- CARA ---------------------------------------*/

typedef struct {
    vector3d normal;
    int numeroVertices;    /** cuantos vertices tiene **/
    int *tablaVertices;    /** indice de los vertices, que forman la cara, en la tabla de vertices **/ 
} cara;

/*----------------------- OBJETO -----------------------------------------*/
typedef struct OBJETO{
    int numeroVertices;       /** numero de vertices del objeto **/
    vertice *tablaVertices;   /** tabla de vertices **/
    int numeroCaras;          /** numero de caras del objeto **/ 
    cara *tablaCaras;         /** tabla de caras **/
    punto3d min;              // coordenada minima del objeto
    punto3d max;              // coordenada maxima del objeto
} OBJETO;

/*----------------------- CAMARA -----------------------------------------*/

typedef struct camara {
	punto3d posicion;
	punto3d pmira;
	vector3d vup;
	vector3d vdir;
} camara;

/*----------------------- LUZ -----------------------------------------*/

typedef struct luz {
	float ambiente[4];
	float difuso[4];
	float especular[4];
	float posicion[4];
} luz;
/*----------------------- LISTA DE LUCES -----------------------------------------*/

#endif // DEFINICION_H
