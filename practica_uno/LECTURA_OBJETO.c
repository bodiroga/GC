
/// int lecturaObjeto(char *nombreFichero, objeto *objetoptr){
/// lee los datos del archivo y genera la estructura tipo "OBJETO"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "definicion.h" 

#define MAXLINE 200


static int sreadint(char * linea, int * numeros)
{
    char *s = linea;
    int i, numero, cont=0;

    while (sscanf(s," %d%n", &numero, &i)>0) {
        s += i;
        numeros[cont++] = numero;
    }
    return(cont);
}


int lecturaObjeto(char *nombreFichero, OBJETO *objetoptr){
    vertice *tablavert;
    cara *tablacaras;
    int numvert=-1,numcaras=-1, contVertices=0, contCaras=0;
    FILE *idFichero;
    char linea[MAXLINE], linea1[MAXLINE], resto[45];
    int k;
    int i,j;
    int valores[MAXLINE];
    
    /* Primera lectura del fichero ***************************/
    
    if ((idFichero = fopen(nombreFichero,"r"))==NULL)
    {
        printf("No encuentro el fichero %s !!!!!\n",nombreFichero);
        return(-1);
    }
    while (fscanf(idFichero,"\n%[^\n]",linea)>0)
    {
        i=0;
        while (linea[i] == ' ') i++;
        if ((linea[0] == '#') && ((int)strlen(linea)>5))
        {
            i+=2;
            j=0;
            while (linea[i]!= ' ') linea1[j++]=linea[i++];
            i++;
            linea1[j]='\0';
            j=0;
            while ((linea[i]!= ' ') && (linea[i]!='\0'))
                resto[j++]=linea[i++];
            resto[j]=0;
            if (strcmp(resto,"vertices")==0) {
                numvert=atoi(linea1);
           }
            if (strncmp(resto,"elements",7)==0) {
                numcaras=atoi(linea1);
            }
        } else {
            if (strlen(linea)>6) {
                if (linea[i] == 'f' && linea[i+1] == ' ')
                    contCaras++;
                else if (linea[i] == 'v' && linea[i+1] == ' ')
                    contVertices++;
            }
        }
    }
    fclose(idFichero);


    if ((numvert != -1 && numvert != contVertices) && (numcaras != -1 && numcaras != contCaras))
    {
        printf("Fichero mal definido: (%s)\n",nombreFichero);
        return(-2);
    }
    if (numvert == 0 || contVertices ==0)
    {
        printf("No se encuentran vertices: (%s)\n",nombreFichero);
        return(3);
    }
    if (numcaras == 0 ||  contCaras == 0)
    {
        printf("No se encuentran caras: (%s)\n",nombreFichero);
        return(3);
    } 

    numvert = contVertices;
    numcaras = contCaras;

 


    tablavert = (vertice *)malloc(numvert*sizeof(vertice));
    tablacaras = (cara *)malloc(numcaras*sizeof(cara));
    
    /*** Segunda lectura del fichero  *****************/
    
    idFichero=fopen(nombreFichero,"r");
    k=0;
    j=0;
    
    for (i=0;i<numvert;i++)
        tablavert[i].numeroCaras = 0;
    
    while (fscanf(idFichero,"\n%[^\n]",linea)>0)
    {
        switch (linea[0])
        {
        case 'v':
            {
                sscanf(linea+2,"%lf%lf%lf",&(tablavert[k].coord.x),
                       &(tablavert[k].coord.y), &(tablavert[k].coord.z));
                k++;
            }
            break;
            
        case 'f':
            {
                for (i=2; i<=(int)strlen(linea); i++)
                    linea1[i-2]=linea[i];
                tablacaras[j].numeroVertices = sreadint(linea1,valores);
                tablacaras[j].tablaVertices = (int *)malloc(tablacaras[j].numeroVertices*sizeof(int));
                for (i=0; i<tablacaras[j].numeroVertices; i++)
                {
                    tablacaras[j].tablaVertices[i] = valores[i]-1;
                    tablavert[tablacaras[j].tablaVertices[i]].numeroCaras++;
                }
                j++;
            }
            break;
        }
    }
    
    fclose(idFichero);
    
    objetoptr->tablaVertices = tablavert;
    objetoptr->tablaCaras = tablacaras;
    objetoptr->numeroVertices = numvert;
    objetoptr->numeroCaras = numcaras;

	/* ahora vamos a calcular el punto mnimo y el punto mximo */

	objetoptr->max.x =objetoptr->tablaVertices[0].coord.x;

	objetoptr->max.y = objetoptr->tablaVertices[0].coord.y;

	objetoptr->max.z = objetoptr->tablaVertices[0].coord.z;

	objetoptr->min.x = objetoptr->tablaVertices[0].coord.x;

	objetoptr->min.y = objetoptr->tablaVertices[0].coord.y;

	objetoptr->min.z = objetoptr->tablaVertices[0].coord.z;

	for( i=1; i<objetoptr->numeroVertices; i++) {

		if(objetoptr->tablaVertices[i].coord.x < objetoptr->min.x)

			objetoptr->min.x = objetoptr->tablaVertices[i].coord.x;

		if(objetoptr->tablaVertices[i].coord.y < objetoptr->min.y)

			objetoptr->min.y = objetoptr->tablaVertices[i].coord.y;

		if(objetoptr->tablaVertices[i].coord.z < objetoptr->min.z)

			objetoptr->min.z = objetoptr->tablaVertices[i].coord.z;

		if(objetoptr->tablaVertices[i].coord.x > objetoptr->max.x)

			objetoptr->max.x = objetoptr->tablaVertices[i].coord.x;

		if(objetoptr->tablaVertices[i].coord.y > objetoptr->max.y)

			objetoptr->max.y = objetoptr->tablaVertices[i].coord.y;

		if(objetoptr->tablaVertices[i].coord.z > objetoptr->max.z)

			objetoptr->max.z = objetoptr->tablaVertices[i].coord.z;

	}
    return(0);
}
