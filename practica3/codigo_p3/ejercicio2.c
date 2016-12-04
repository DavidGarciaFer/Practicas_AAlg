/***********************************************************/
/* Programa: ejercicio2 Fecha:                             */
/* Autores:                                                */
/*                                                         */
/* Programa que escribe en un fichero                      */
/* los tiempos medios del algoritmo de                     */
/* busqueda                                                */
/*                                                         */
/* Entrada: Linea de comandos                              */
/* -num_min: numero minimo de elementos de la tabla        */
/* -num_max: numero minimo de elementos de la tabla        */
/* -incr: incremento                                       */
/* -fclaves: numero de claves a buscar                     */
/* -numP: Introduce el numero de permutaciones a promediar */
/* -fichSalida: Nombre del fichero de salida               */
/*                                                         */
/* Salida: 0 si hubo error                                 */
/*        -1 en caso contrario                             */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutaciones.h"
#include "busqueda.h"
#include "tiempos.h"

#define NVECES_DET 1

int main(int argc, char** argv)
{
  int i, num_min,num_max,incr,n_veces;
  char nombre[256], fichero1[256], fichero2[256], fichero3[256], fichero4[256];
  short ret;

  srand(time(NULL));

  if (argc != 11) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -n_veces <int> -fichSalida <string> \n");
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, "-num_min: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-num_max: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-incr: incremento\n");
    fprintf(stderr, "-n_veces: numero de veces que se busca cada clave\n");
    fprintf(stderr, "-fichSalida: Nombre del fichero de salida\n");
    exit(-1);
  }

  printf("Practica numero 3, apartado 2\n");
  printf("Realizada por: Vuestros nombres\n");
  printf("Grupo: Vuestro grupo\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc ; i++) {
    if (strcmp(argv[i], "-num_min") == 0) {
      num_min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-num_max") == 0) {
      num_max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-incr") == 0) {
      incr = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-n_veces") == 0) {
      n_veces = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-fichSalida") == 0) strcpy(nombre, argv[++i]);
      else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
      exit(-1);
    }
  }

  /*Creamos los nombres de los ficheros*/

  strcpy(fichero1, nombre);
  strcat(fichero1, "_blin.txt");
  strcpy(fichero2, nombre);
  strcat(fichero2, "_bbin.txt");
  strcpy(fichero3, nombre);
  strcat(fichero3, "_blin_auto.txt");
  strcpy(fichero4, nombre);
  strcat(fichero4, "_bbin_pot.txt");

  /* calculamos los tiempos */
  ret = genera_tiempos_busqueda(blin, generador_claves_uniforme, NO_ORDENADO,
                                fichero1, num_min, num_max, incr, NVECES_DET);
  if (ret == ERR) {
    exit(-1);
  }

  printf("Fichero %s creado correctamente.\n", fichero1);

  ret = genera_tiempos_busqueda(bbin, generador_claves_uniforme, ORDENADO,
                                fichero2, num_min, num_max, incr, NVECES_DET);
  if (ret == ERR){
    exit(-1);
  }

  printf("Fichero %s creado correctamente.\n", fichero2);

  ret = genera_tiempos_busqueda(blin_auto, generador_claves_potencial, NO_ORDENADO,
                                fichero3, num_min, num_max, incr, n_veces);
  if (ret == ERR){
    exit(-1);
  }

  printf("Fichero %s creado correctamente.\n", fichero3);

  ret = genera_tiempos_busqueda(bbin, generador_claves_potencial, ORDENADO,
                                fichero4, num_min, num_max, incr, n_veces);
  if (ret == ERR){
    exit(-1);
  }

  printf("Fichero %s creado correctamente.\n", fichero4);
  printf("Salida correcta \n");

  return 0;
}
