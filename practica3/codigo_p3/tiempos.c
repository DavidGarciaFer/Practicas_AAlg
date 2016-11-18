/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */

#include "tiempos.h"
#include "permutaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

/***************************************************/
/* Funcion: tiempo_medio_ordenacion    Fecha:      */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que almacena en un estructura de tipo    */
/* tiempo el tamaño de las permutaciones, el       */
/* número de permutaciones, el tiempo medio de     */
/* ejecución, número medio, mínimo y máximo de OB  */
/* ejecutadas.                                     */
/*                                                 */
/* Entrada:                                        */
/*  pfunc_ordena metodo: rutina de la que se       */
/*medirá el tiempo.                                */
/*  int n_perms: número de permutaciones           */
/*  int tamanio: tamaño de las permutaciones       */
/* PTIEMPO ptiempo: puntero a la estructura tiempo */
/*                                                 */
/* Salida:                                         */
/*  OK si todo fue bien.                           */
/*  ERR en caso de error                           */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int tamanio,
                              PTIEMPO ptiempo)
{
	int i, min = INT_MAX, max = 0, suma_ob = 0;
	int *ob, **permutaciones;
	double suma_t = 0;
	double *t_medio;
	clock_t t_ini, t_fin;

	if(!metodo || n_perms <=0 || tamanio <=0 || !ptiempo) return ERR;

	ob = (int*)malloc(sizeof(int)*n_perms);
	if(!ob) return ERR;

	t_medio = (double*)malloc(sizeof(double)*n_perms);
	if(!t_medio){
		free(ob);
		return ERR;
	}

	permutaciones = genera_permutaciones(n_perms, tamanio);
	if(!permutaciones){
		free(ob);
		free(t_medio);
		return ERR;
	}

	for(i = 0; i < n_perms; i++){
		t_ini = clock();
		ob[i] = metodo(permutaciones[i], 0, tamanio - 1);
		t_fin = clock();
		t_medio[i] = (double)(t_fin - t_ini)/CLOCKS_PER_SEC;

		if(ob[i] < 0){
			free(ob);
			free(t_medio);
			for(i = 0; i < n_perms ; i++){
				free(permutaciones[i]);
			}
			free(permutaciones);
			return ERR;
		}

		if(ob[i] < min){
			min = ob[i];
		}

		if(ob[i] > max){
			max = ob[i];
		}
	}

	ptiempo->tamanio = tamanio;
	ptiempo->n_perms = n_perms;
	ptiempo->min_ob = min;
	ptiempo->max_ob = max;

	for(i = 0; i < n_perms; i++){
		suma_ob += ob[i];
		suma_t += t_medio[i];
	}

	ptiempo->tiempo = suma_t/n_perms;
	ptiempo->medio_ob = (double)(suma_ob/n_perms);

	free(ob);
	free(t_medio);

	for(i = 0; i < n_perms ; i++){
		free(permutaciones[i]);
	}

	free(permutaciones);

	return OK;

}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion    Fecha:    */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que llama al resto con diferentes        */
/* tamaños de las permutaciones                    */
/*                                                 */
/* Entrada:                                        */
/*  pfunc_ordena metodo: rutina de la que se       */
/*medirá el tiempo.                                */
/* char* fichero: fichero donde se escribirán los  */
/* datos                                           */
/*  int num_min: tamaño mínimo de las permutaciones*/
/*  int num_max: tamaño máximo de las permutaciones*/
/*  int incr: incremento del tamaño de las         */
/* permutaciones                                   */
/* int n_perms: número de permutaciones para cada  */
/* tamaño                                          */
/*                                                 */
/* Salida:                                         */
/*  OK si todo fue bien                            */
/*  ERR en caso de error                           */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_perms)
{
	TIEMPO** tiempo; /*Esto es un array de punteros a tiempo*/
	int i, j, N;

	if(!metodo || !fichero || num_min <= 0 || num_max <= 0 || num_max <= num_min || incr <= 0 || n_perms <= 0) return ERR;

	N = ((num_max - num_min) / incr) + 1;

	tiempo = (TIEMPO**)malloc(sizeof(TIEMPO*)*N); /*Reservo memoria para el array de punteros a tiempo*/

	for(i = num_min, j = 0 ; i <= num_max; i = i + incr, j++){

		/*Reservo memoria para cada puntero a tiempo en cada iteración*/

		tiempo[j] = (TIEMPO*)malloc(sizeof(TIEMPO));
		if(!tiempo[j]){

			for(j = j - 1; j >= 0 ; j--){
				free(tiempo[j]);
			}
			free(tiempo);
			return ERR;
		}

		if(tiempo_medio_ordenacion(metodo, n_perms, i, tiempo[j]) == ERR){
			for(i = 0; i < N ; i++){
				free(tiempo[i]);
			}
			free(tiempo);
			return ERR;

		}
	}


	if(guarda_tabla_tiempos(fichero, tiempo, N) == ERR){
		for(i = 0; i < N ; i++){
				free(tiempo[i]);
			}
		free(tiempo);
		return ERR;
	}

	for(i = 0; i < N ; i++){
		free(tiempo[i]);
	}
	free(tiempo);

	return OK;

}

/***************************************************/
/* Funcion: guarda_tabla_tiempos    Fecha:         */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que escribe en un fichero los datos de   */
/* la estructura tiempo                            */
/*                                                 */
/* Entrada:                                        */
/* char* fichero: fichero donde se escribirán los  */
/* datos                                           */
/* PTIEMPO* ptiempo: tabla de punteros a           */
/* estructuras de tipo tiempo                      */
/*  int N: tamaño de la tabla de punteros a tiempo */
/*                                                 */
/* Salida:                                         */
/*  OK si todo fue bien                            */
/*  ERR en caso de error                           */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO* tiempo, int N){

	int i;
	FILE *f;

	if(!fichero || !tiempo || N <= 0) return ERR;

	f = fopen(fichero, "w");
	if(!f) return ERR;

	fprintf(f,"Tamaño\tTiempo promedio\tPromedio OB\tMin OB\tMax OB\n\n");

	for(i = 0; i < N; i++){
		fprintf(f, "%d\t%.7f\t%.3f\t%d\t%d\n", tiempo[i]->tamanio, tiempo[i]->tiempo, tiempo[i]->medio_ob, tiempo[i]->min_ob, tiempo[i]->max_ob);

  }

	fclose(f);

	return OK;
}
