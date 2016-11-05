/**************************************************/
/* Programa: ejercicio4       Fecha:              */
/* Autores:                                       */
/*                                                */
/* Programa que Comprueba SelectSort              */
/*                                                */
/* Entrada: Linea de comandos                     */
/* -tamanio: numero elementos permutacion         */
/* Salida: 0: OK, -1: ERR                         */
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutaciones.h"
#include "ordenacion.h"

int main(int argc, char** argv)
{
  int tamano, i, j, ret, tipo;
  int* perm = NULL;
  char metodo[256];
  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -tamanio <int> -metodo <char*> -tipo <int> \n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -tamanio : numero elementos permutacion.\n");
	fprintf(stderr, " -metodo : nombre del algoritmo (quicksort o mergesort)\n");
    fprintf(stderr, " -tipo : entero que identifica la eleccion del pivote, en el caso de quicksort. \nSiendo 1 FIRST, 2 AVERAGE, 3 STAT.\n En mergesort introducir un entero cualquiera.\n");
    return 0;
  }
  printf("Practica numero 1, apartado 4\n");
  printf("Realizada por: David García y Antonio Martín\n");
  printf("Grupo: grupo 1201 - Pareja 1\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-tamanio") == 0) {
      tamano = atoi(argv[++i]);
    } 
    else if (strcmp(argv[i], "-tipo") == 0){
      tipo = atoi(argv[++i]);
    }
	else if (strcmp(argv[i], "-metodo") == 0){
	  strcpy(metodo, argv[++i]);
	/*  if(!metodo){
		printf("Error al reservar memoria para el metodo.\n");		
		return -1;
      }*/
	}
    else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  perm = genera_perm(tamano);

  if (perm == NULL) { /* error */
    printf("Error: No hay memoria\n");
    exit(-1);
  }
  
  if(strcmp(metodo, "mergesort") == 0){
	ret = mergesort(perm, 0, tamano - 1);
	if (ret == ERR) {
    	printf("Error: Error en MergeSort\n");
    	free(perm);
    	exit(-1);
  	}
  }
  else if(strcmp(metodo, "quicksort") == 0){
  	ret = quicksort(perm, 0, tamano - 1, tipo);

  	if (ret == ERR) {
    	printf("Error: Error en QuickSort\n");
   	 	free(perm);
    	exit(-1);
  	}
  }

  else{
	printf("Error en el parámetro método.\n");
	free(perm);
	return -1;
}
  for(j = 0; j < tamano; j++) {
    printf("%d \t", perm[j]);
  }
  printf("\n");

/*Imprimimos por pantalla el número de veces que se ejecuta la operación básica*/

  printf("Número de veces que se ejecuta la OB: %d\n", ret);

  free(perm);

  return 0;
}

