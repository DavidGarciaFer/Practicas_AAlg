/**
 *
 * Descripcion: Funciones de cabecera para ordenacion 
 *
 * Fichero: ordenacion.h
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */

#ifndef ORDENACION_H
#define ORDENACION_H

/* constantes */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* definiciones de tipos */
typedef int (* pfunc_ordena)(int*, int, int);

/* Funciones */

int InsertSort(int* tabla, int ip, int iu);
int InsertSortInv(int* tabla, int ip, int iu);
int mergesort(int* tabla, int ip, int iu);
int quicksort(int* tabla, int ip, int iu, int tipo);
int quicksortFIRST(int* tabla, int ip, int iu);
int quicksortAVG(int* tabla, int ip, int iu);
int quicksortSTAT(int* tabla, int ip, int iu);

#endif
