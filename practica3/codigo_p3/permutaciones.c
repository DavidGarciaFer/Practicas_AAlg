/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */


#include "permutaciones.h"
#include <stdio.h>
#include <stdlib.h>

/***************************************************/
/* Funcion: aleat_num Fecha:                       */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup)
{	
	if(inf <= 0 || sup <= 0 || inf > sup ){
		return ERR;
	}
		
	return (rand() % (sup - inf + 1)) + inf;
}

/***************************************************/
/* Funcion: genera_perm Fecha:                     */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/


int* genera_perm(int n){
	
	int* perm;
	int random, buff, i;

	perm = (int*)malloc(sizeof(int)*n);

	if(!perm) return NULL;

	for(i = 0; i < n ; i++){
		perm[i] = (i+1);
	}	

	for(i = 0; i < n-1 ; i++){
		
		/*Creamos el indice de la permutación con la que intercambiaremos el número aleatoriamente*/

		random = aleat_num(i+1, n-1);

		/*Swap*/

		buff = perm[i];
		perm[i] = perm[random];
		perm[random] = buff;
	}

	return perm;
	
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha:            */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int tamanio: Numero de elementos de cada        */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int tamanio){

	int**perms;
	int i;

	perms = (int**)malloc(n_perms*sizeof(int*));

	if(!perms) return NULL;
		

	for(i = 0; i < n_perms ; i++){

		perms[i] = genera_perm(tamanio);

		if(!perms[i]){
			for(i--; i >= 0 ; i--){
				free(perms[i]);
			}
			free(perms);
			return NULL;
		}

	}

	return perms;
}
