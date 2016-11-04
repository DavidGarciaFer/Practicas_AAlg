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

/***************************************************/
/* Funcion: InsertSort    Fecha:                   */
/* Vuestro comentario                              */
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
/* Funcion: InsertSortInv    Fecha:                   */
/* Vuestro comentario                              */
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

