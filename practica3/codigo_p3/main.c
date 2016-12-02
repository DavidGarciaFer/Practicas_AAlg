#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#include "ordenacion.h"
#include "busqueda.h"
#include "permutaciones.h"

int main(){

    int tabla[4] = {1, 2, 3, 4};
    int nob, clave, pos, tamanio;
    PDICC pdicc;

    clave = 4;
    tamanio = 4;

    pdicc = ini_diccionario(tamanio,ORDENADO);

    if (pdicc == NULL) {
      /* error */
      printf("Error: No se puede Iniciar el diccionario\n");
      exit(-1);
    }

    nob = insercion_masiva_diccionario(pdicc, tabla, tamanio);

    if (nob == ERR) {
      /* error */
      printf("Error: No se puede crear el diccionario memoria\n");
      libera_diccionario(pdicc);
      exit(-1);
    }

    /*Realizamos busqueda binaria*/

    nob = busca_diccionario(pdicc,clave,&pos,bbin);

    if(nob >= 0) {
      printf("Búsqueda binaria:\n");
      printf("Clave %d encontrada en la posicion %d en %d op. basicas\n",clave,pos,nob);
    } else if (nob==NO_ENCONTRADO) {
      printf("La clave %d no se encontro en la tabla\n",clave);
    } else {
      printf("Error al buscar la clave %d\n",clave);
    }

    /*Realizamos búsqueda lineal ordenada*/

    nob = busca_diccionario(pdicc,clave,&pos,blin);

    if(nob >= 0) {
      printf("Búsqueda lineal ordenada:\n");
      printf("Clave %d encontrada en la posicion %d en %d op. basicas\n",clave,pos,nob);
    } else if (nob==NO_ENCONTRADO) {
      printf("La clave %d no se encontro en la tabla\n",clave);
    } else {
      printf("Error al buscar la clave %d\n",clave);
    }

    libera_diccionario(pdicc);


    return EXIT_SUCCESS;

}
