/***********************************************************/
/* Programa: ejercicio5                  Fecha:            */
/* Autores:                                                */
/*                                                         */
/* Programa que escribe en un fichero                      */
/* los tiempos medios del algoritmo de                     */
/* ordenacion por Seleccion                                */
/*                                                         */
/* Entrada: Linea de comandos                              */
/* -num_min: numero minimo de elementos de la tabla        */
/* -num_max: numero minimo de elementos de la tabla        */
/* -incr: incremento\n                                     */
/* -numP: Introduce el numero de permutaciones a promediar */
/* -fichSalida: Nombre del fichero de salida               */
/* Salida: 0 si hubo error                                 */
/* -1 en caso contrario                                    */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ordenacion.h"
#include "tiempos.h"

int main(int argc, char** argv)
{
  int i, num_min, num_max, incr, n_perms;
  char nombre[256], nombreMs[256], nombreQs1[256], nombreQs2[256], nombreQs3[256];
  short ret;

  srand(time(NULL));

  if (argc != 11) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -numP <int> -fichSalida <string> \n");
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, "-num_min: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-num_max: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-incr: incremento\n");
    fprintf(stderr, "-numP: Introduce el numero de permutaciones a promediar\n");
    fprintf(stderr, "-fichSalida: Nombre del fichero de salida\n");
    exit(-1);
  }

  printf("Practica numero 1, apartado 5\n");
  printf("Realizada por: David García y Antonio Martín\n");
  printf("Grupo: grupo 1201 - Pareja 1\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc ; i++) {
    if (strcmp(argv[i], "-num_min") == 0) {
      num_min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-num_max") == 0) {
      num_max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-incr") == 0) {
      incr = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      n_perms = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-fichSalida") == 0) {
      strcpy(nombre, argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  strcpy(nombreMs, nombre);
  strcpy(nombreQs1, nombre);
  strcpy(nombreQs2, nombre);
  strcpy(nombreQs3, nombre);

  strcat(nombreMs, "_MS.txt");
  strcat(nombreQs1, "_QS_First.txt");
  strcat(nombreQs2, "_QS_Average.txt");
  strcat(nombreQs3, "_QS_Stat.txt");
	

  /* Calculamos los tiempos de MergeSort*/

  ret = genera_tiempos_ordenacion(mergesort, nombreMs,num_min, num_max,incr, n_perms);
  if (ret == ERR) { /* ERR_TIME debera ser un numero negativo */
    printf("Error en la funcion Time_Ordena\n");
    exit(-1);
  }
  printf("Salida correcta \n");

  /* Calculamos los tiempos de QuickSort First*/

  ret = genera_tiempos_ordenacion(quicksortFIRST, nombreQs1,num_min, num_max,incr, n_perms);
  if (ret == ERR) { /* ERR_TIME debera ser un numero negativo */
    printf("Error en la funcion Time_Ordena\n");
    exit(-1);
  }
  printf("Salida correcta \n");

  /* Calculamos los tiempos de QuickSort Average*/

  ret = genera_tiempos_ordenacion(quicksortAVG, nombreQs2,num_min, num_max,incr, n_perms);
  if (ret == ERR) { /* ERR_TIME debera ser un numero negativo */
    printf("Error en la funcion Time_Ordena\n");
    exit(-1);
  }
  printf("Salida correcta \n");

  /* Calculamos los tiempos de QuickSort Stat*/

  ret = genera_tiempos_ordenacion(quicksortSTAT, nombreQs3,num_min, num_max,incr, n_perms);
  if (ret == ERR) { /* ERR_TIME debera ser un numero negativo */
    printf("Error en la funcion Time_Ordena\n");
    exit(-1);
  }
  printf("Salida correcta \n");

  return 0;
}

