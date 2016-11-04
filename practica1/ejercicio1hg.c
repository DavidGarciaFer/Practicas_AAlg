/***********************************************/
/* Programa: ejercicio1     Fecha:             */
/* Autores:                                    */
/*                                             */
/* Programa que genera numeros aleatorios      */
/* entre dos numeros dados                     */
/*                                             */
/* Entrada: Linea de comandos                  */
/* -limInf: limite inferior                    */
/* -limSup: limite superior                    */
/* -numN: cantidad de numeros                  */
/* Salida: 0: OK, -1: ERR                      */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutaciones.h"

int main(int argc, char** argv)
{
  int i, buff;
  unsigned int inf, sup, num, j;
  FILE* salida;
  int* frecuencia;

  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -limInf : Limite inferior.\n");
    fprintf(stderr, " -limSup : Limite superior.\n");
    fprintf(stderr, " -numN : Cantidad de numeros a generar.\n");
    exit(-1);
  }
  printf("Practica numero 1, apartado 1 (GENERACION DE DATOS PARA HISTOGRAMA)\n");
  printf("Realizada por: David García y Antonio Martín.\n");
  printf("Grupo: Grupo 1.\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-limInf") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-limSup") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
      num = atoi(argv[++i]);
    }else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    } 
    
  }
  
	if(inf >= sup){
    	printf("El límite inferior debería ser estrictamente menor que el límite superior.\n");
    	return ERR;
    }

  /*ESTE CÓDIGO SIRVE PARA CREAR UN ARCHIVO CON EL FORMATO DE GNUPLOT*/

  /*Abrimos el fichero en el que guardaremos los datos para realizar el histograma*/

  salida = fopen("datos.txt", "w");

  if(!salida) return ERR;

  /*Reservo memoria para una tabla de enteros de tamaño limSup - limInf (cantidad de números que vamos a generar)*/

  frecuencia = (int*)malloc(sizeof(int)*(sup-inf+1));

  if(!frecuencia){
    fclose(salida);
    return ERR;
  }

  /*Inicializamos todos los valores de la tabla a cero*/

  for(i = 0 ; i < sup-inf+1 ; i++){
    frecuencia[i]=0;
  }

  /*Comenzamos un bucle que vaya creando los números aleatoriamente*/


  for(j = 0; j < num ; j++){
    /*Primero creamos el número aleatorio*/
    buff = aleat_num(inf, sup);
    /*Imprimimos el número por pantalla*/
    printf("%d\n", buff);
    /*Lo almacenamos en la tabla*/
    buff = buff-inf;
    frecuencia[buff]++;
  }

  /*Una vez creada la tabla de frecuencias la guaradamos en el fichero de texto*/

  for (i = 0; i < sup-inf+1; i++)
  {
    fprintf(salida, "%d \t %d \n", i+inf, frecuencia[i]);
  }

  /*Cerramos el fichero de salida*/

  fclose(salida);

  /*Liberamos memoria de la tabla de frecuencias*/

  free(frecuencia);

  return 0;
}



