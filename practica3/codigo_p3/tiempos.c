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


/***************************************************/
/* Funcion: genera_tiempos_busqueda      Fecha:    */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que llama al resto con diferentes        */
/* tamaños de los diccionarios                     */
/*                                                 */
/* Entrada:                                        */
/*  pfunc_busqueda metodo: rutina de la que se     */
/*medirá el tiempo.                                */
/*  pfunc_generador_claves generador: rutina que   */
/*generará las claves a buscar                     */
/*  int orden: diccionario ORDENADO o NO_ORDENADO  */
/* char* fichero: fichero donde se escribirán los  */
/* datos                                           */
/*  int num_min: tamaño mínimo de los diccionarios */
/*  int num_max: tamaño máximo de los diccionarios */
/*  int incr: incremento del tamaño de los         */
/* diccionarios                                    */
/* int n_veces: número de veces que se buscará     */
/* cada clave                                      */
/*                                                 */
/* Salida:                                         */
/*  OK si todo fue bien                            */
/*  ERR en caso de error                           */
/***************************************************/
short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                                int orden, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_veces){
  TIEMPO** tiempo;
  int i, j, N;

  if(!metodo || !generador || !fichero || num_min <= 0 || num_max < num_min || incr <= 0 || n_veces <= 0 || (orden != ORDENADO && orden != NO_ORDENADO))
    return ERR;

  N = ((num_max - num_min) / incr) + 1;

  tiempo = (TIEMPO**)malloc(sizeof(TIEMPO*)*N);

  for(i = num_min, j=0; i <= num_max ; i = i+incr, j++){
    tiempo[j] = (TIEMPO*)malloc(sizeof(TIEMPO));
		if(!tiempo[j]){
			for(j = j - 1; j >= 0 ; j--){
				free(tiempo[j]);
			}
			free(tiempo);
			return ERR;
		}

    if(tiempo_medio_busqueda(metodo, generador, orden, i, i, n_veces, tiempo[j]) == ERR){
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
/* Funcion: tiempo_medio_busqueda      Fecha:      */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que almacena en un estructura de tipo    */
/* tiempo el tamaño de los diccionarios, el        */
/* el tiempo medio de ejecución, número medio,     */
/*  mínimo y máximo de OB ejecutadas.              */
/*                                                 */
/* Entrada:                                        */
/*  pfunc_busqueda metodo: rutina de la que se     */
/*medirá el tiempo.                                */
/*  int n_claves: número de claves a buscar        */
/*  pfunc_geenrador_claves generador: rutina que   */
/*generará las claves.                             */
/*  int orden: diccionario ORDENADO o NO_ORDENADO  */
/*  int tamanio: tamaño del diccionario            */
/*  int n_veces: número de veces que se buscará    */
/* cada clave                                      */
/* PTIEMPO ptiempo: puntero a la estructura tiempo */
/*                                                 */
/* Salida:                                         */
/*  OK si todo fue bien.                           */
/*  ERR en caso de error                           */
/***************************************************/
short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio,
                              int n_claves,
                              int n_veces,
                              PTIEMPO ptiempo){
  int *ob, *claves, *permutacion, error, min = INT_MAX, max = 0, ppos, ret = 0, ret2, i;
  PDICC dicc;
  double t_medio = 0, obmedio = 0;
  clock_t t_ini, t_fin;

  if(!metodo || !generador || (orden != ORDENADO && orden != NO_ORDENADO) || tamanio <= 0 || n_claves <= 0 || n_veces <= 0 || !ptiempo)
    return ERR;

  dicc = ini_diccionario(tamanio, orden);
  if(!dicc)
    return ERR;

  ob = (int*)malloc(sizeof(int)*n_claves);
  if(!ob){
    libera_diccionario(dicc);
    return ERR;
  }

  permutacion = genera_perm(n_claves);
  if(!permutacion){
    libera_diccionario(dicc);
    free(ob);
    return ERR;
  }

  error = insercion_masiva_diccionario(dicc, permutacion, n_claves);
  if(error == ERR){
    libera_diccionario(dicc);
    free(ob);
    return ERR;
  }

  claves = (int*)malloc(sizeof(int)*n_claves*n_veces);
  if(!claves){
    free(ob);
    libera_diccionario(dicc);
    free(permutacion);
    return ERR;
  }

  generador(claves, n_veces*n_claves, n_claves);

  for(i = 0; i < n_claves*n_veces; i++){
      t_ini = clock();
      ret2 = busca_diccionario(dicc, claves[i], &ppos, metodo);
      t_fin = clock();
      ret += ret2;
      if(ret2 < min )
        min = ret2;
      if(ret2 > max)
        max = ret2;
      t_medio += (double)(t_fin - t_ini)/CLOCKS_PER_SEC;
  }

  obmedio =(double) ret/(n_veces*n_claves);
  t_medio = t_medio/(n_veces*n_claves);

  /*Actualizamos la estructura de tiempo*/

  ptiempo->tamanio = tamanio;
  ptiempo->n_perms = n_claves;
  ptiempo->n_veces = n_veces;
  ptiempo->tiempo = t_medio;
  ptiempo->medio_ob = obmedio;
  ptiempo->min_ob = min;
  ptiempo->max_ob = max;

  free(ob);
  libera_diccionario(dicc);
  free(permutacion);
  free(claves);

  return OK;

}
