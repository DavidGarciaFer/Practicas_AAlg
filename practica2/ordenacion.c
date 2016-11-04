/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */


#include "ordenacion.h"
#include <stdio.h>
#include <stdlib.h>


/***************************************************/
/* Funcion: InsertSort    Fecha:                   */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que ordena una tabla de menor a mayor    */
/*                                                 */
/* Entrada:                                        */
/*  int* tabla: tabla de enteros a ordenar         */
/*  int ip: primer índice de la tabla              */
/*  int iu: último índice de la tabla              */
/*                                                 */
/* Salida:                                         */
/*  int: número de veces que se ejecuta la OB      */
/*  -1 en caso de error                            */
/***************************************************/
int InsertSort(int* tabla, int ip, int iu){

	int i, j, buff, swap, counter;
	
	if(!tabla || iu < ip) return -1;
	
	counter = 0;
	
	for( i = ip + 1 ; i <= iu ; i++){
		buff = tabla[i];
		j = i - 1;
		
		
		while( j >= ip && tabla[j] > buff){
			swap = tabla[j+1];
			tabla[j+1] = tabla[j];
			tabla[j] = swap;
			j--;
			counter++;
		}
		if(j >= ip) counter++;
		tabla[j+1] = buff;		
	}
	  
	return counter;
}

/***************************************************/
/* Funcion: InsertSortInv    Fecha:                */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que ordena una tabla de mayor a menor    */
/*                                                 */
/* Entrada:                                        */
/*  int* tabla: tabla de enteros a ordenar         */
/*  int ip: primer índice de la tabla              */
/*  int iu: último índice de la tabla              */
/*                                                 */
/* Salida:                                         */
/*  int: número de veces que se ejecuta la OB      */
/*  -1 en caso de error                            */
/***************************************************/
int InsertSortInv(int* tabla, int ip, int iu)
{
  int i, j, buff, swap, counter;
	
	if(!tabla || iu < ip) return -1;
	
	counter = 0;
	
	for( i = ip + 1 ; i <= iu ; i++){
		buff = tabla[i];
		j = i - 1;
		
		while( j >= ip && tabla[j] < buff){
			swap = tabla[j+1];
			tabla[j+1] = tabla[j];
			tabla[j] = swap;
			j--;
			counter++;
		}
		if(j >= ip) counter++;
		tabla[j+1] = buff;		
	}
	  
	return counter;
}

/***************************************************/
/* Funcion: merge  Fecha:21/10/2016                */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que combina las tablas de mergesort      */
/*                                                 */
/* Entrada:                                        */
/*  int* tabla: tabla de enteros a ordenar         */
/*  int ip: primer índice de la tabla              */
/*  int iu: último índice de la tabla              */
/*  int imedio: índice de la posición media        */
/*                                                 */
/* Salida:                                         */
/*  int: número de veces que se ejecuta la OB      */
/*  -1 en caso de error                            */
/***************************************************/

int merge(int* tabla, int ip, int iu, int imedio){
	int *taux, i, j, k, counter = 0;
	
	taux = (int*)calloc((iu - ip + 1), sizeof(int));
	if(!taux) return ERR;
	
	i = ip;
	j = imedio + 1;
	k = 0;
	
	while(i <= imedio && j <= iu){
		if(tabla[i] < tabla[j]){
			taux[k] = tabla[i];
			i++;			
		}
		else{
			taux[k] = tabla[j];
			j++;
		}
		k++;
		counter++;	
	}
		
	if(i > imedio){
		while(j <= iu){
			taux[k] = tabla[j];
			j++;
			k++;
		}				
	}
	else if(j > iu){
		while(i <= imedio){
			taux[k] = tabla[i];
			i++;
			k++;
		}
	}
				
	for(i = ip; i < iu + 1; i++){
		tabla[i] = taux[i - ip];
	}
	
	free(taux);
		
	return counter;
}

/***************************************************/
/* Funcion: mergesort   Fecha:21/10/2016           */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que ordena una tabla de mayor a menor    */
/* por el método MergeSort                         */
/*                                                 */
/* Entrada:                                        */
/*  int* tabla: tabla de enteros a ordenar         */
/*  int ip: primer índice de la tabla              */
/*  int iu: último índice de la tabla              */
/*  int imedio: índice de la posición media        */
/*                                                 */
/* Salida:                                         */
/*  int: número de veces que se ejecuta la OB      */
/*  -1 en caso de error                            */
/***************************************************/


int mergesort(int* tabla, int ip, int iu){
	int a, b, imedio;
	
	if(!tabla || ip < 0 || iu < ip) return ERR;
	if(ip == iu) return 0;
	
	imedio = (ip + iu)/2;
	
	a = mergesort(tabla, ip, imedio);
	if(a == ERR) return ERR;
		
	b = mergesort(tabla, imedio + 1, iu);
	if(b == ERR) return ERR;

	return a + b + merge(tabla, ip, iu, imedio);
}




/***************************************************/
/* Funcion: medio   Fecha:21/10/2016               */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Devuelve la posición del pivote		           */
/*                                                 */
/* Entrada:                                        */
/*  int* tabla: tabla de enteros a ordenar         */
/*  int ip: primer índice de la tabla              */
/*  int iu: último índice de la tabla              */
/*  int *pos: posición del pivote		           */
/*                                                 */
/* Salida:                                         */
/*  int: posición del pivote	                   */ 
/*  -1 en caso de error                            */
/***************************************************/

int medio(int* tabla, int ip, int iu, int* pos, int type){
	
	int medio;
	
	if(!tabla || ip < 0 || ip > iu || !pos) return ERR;
	
	medio = (ip + iu)/2;
	
	switch(type){
		case 1:
			*pos = ip;
			break;
		case 2:
			*pos =(ip + iu)/2;
			break;
		case 3:
			if((tabla[iu] <= tabla[ip] && tabla[iu] >= tabla[medio]) || (tabla[iu] >= tabla[ip] && tabla[iu] <= tabla[medio]))
				*pos = iu;
			else if((tabla[ip] <= tabla[iu] && tabla[ip] >= tabla[medio]) || (tabla[ip] >= tabla[iu] && tabla[ip] <= tabla[medio]))
				*pos = ip;
			else
				*pos = medio;	
			break;
		default:
			return ERR;
	}
	return OK;
	
}

/***************************************************/
/* Funcion: partir   Fecha:21/10/2016              */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Divide la tabla entre elementos mayores y       */
/* que el pivote                                   */
/* Entrada:                                        */
/*  int* tabla: tabla de enteros a ordenar         */
/*  int ip: primer índice de la tabla              */
/*  int iu: último índice de la tabla              */
/*  int *pos: posición del pivote		   		   */
/*                                                 */
/* Salida:                                         */
/*  int: número de veces que se ejecuta la OB      */
/*  -1 en caso de error                            */
/***************************************************/

int partir(int* tabla, int ip, int iu, int* pos, int type){
	
	int k, i, buff, counter = 0;
	
	if(!tabla || ip < 0 || ip > iu || !pos) return ERR;
	
	if(medio(tabla, ip, iu, pos, type) == ERR) /*ACORDARSE DE MODIFICARLO ANTES DE PROBARLO*/	
		return ERR;
	
	k = tabla[*pos];
	
	buff = tabla[ip];
	tabla[ip] = tabla[*pos];
	tabla[*pos] = buff;
	
	*pos = ip;
	
	for(i = ip + 1 ; i <= iu ; i++){
		if(tabla[i] < k){
			(*pos)++;
			buff = tabla[i];
			tabla[i] = tabla[*pos]; /*OJITOOOO*/
			tabla[*pos] = buff;
		}
		counter++;
	}
	
	buff = tabla[ip];
	tabla[ip] = tabla[*pos];
	tabla[*pos] = buff;
	
	return counter;
}

/***************************************************/
/* Funcion: quicksort   Fecha:28/10/2016           */
/* Autores: David García y Antonio Martín          */
/*                                                 */
/* Rutina que ordena una tabla de mayor a menor    */
/* por el método QuickSort                         */
/*                                                 */
/* Entrada:                                        */
/*  int* tabla: tabla de enteros a ordenar         */
/*  int ip: primer índice de la tabla              */
/*  int iu: último índice de la tabla              */
/*                                                 */
/* Salida:                                         */
/*  int: número de veces que se ejecuta la OB      */
/*  -1 en caso de error                            */
/***************************************************/

int quicksort(int* tabla, int ip, int iu, int type){

	int pos, counter = 0;
	
	if(!tabla || ip < 0 || ip > iu || type < 1 || type > 3) return ERR;

	if(ip == iu) return 0;

	counter = partir(tabla, ip, iu, &pos, type);
	if(counter == ERR)
		return ERR;
	
	if(ip < pos)
		counter += quicksort(tabla, ip, pos-1, type);
	
	if(pos < iu)
		counter += quicksort(tabla, pos+1, iu, type);
		
	return counter;
}

/*
	Las funciones siguientes encapsulan la función quicksort,
	las utilizaremos para llamar al ejercicio5.c y poder pasar como
	puntero la función quicksort con cada uno de los pivotes.
*/

int quicksortFIRST(int* tabla, int ip, int iu){
	return quicksort(tabla, ip, iu, 1);
}

int quicksortAVG(int* tabla, int ip, int iu){
	return quicksort(tabla, ip, iu, 2);
}

int quicksortSTAT(int* tabla, int ip, int iu){
	return quicksort(tabla, ip, iu, 3);
}


