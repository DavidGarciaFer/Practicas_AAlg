/*
 *
 * Descripcion: Implementacion funciones para busqueda
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
  }

  return;
}

PDICC ini_diccionario (int tamanio, char orden){

  DICC* diccionario;

  if(tamanio <= 0 || (orden != ORDENADO && orden != NO_ORDENADO)){
    return NULL;
  }
  diccionario = (DICC*)malloc(sizeof(DICC));
  if(!diccionario) return NULL;

  diccionario->tamanio = tamanio;
  diccionario->n_datos = 0;
  diccionario->orden = orden;

  diccionario->tabla = (int*)malloc(sizeof(int)*tamanio);
  if(!diccionario->tabla){
    free(diccionario);
    return NULL;
  }

  return diccionario;

}

void libera_diccionario(PDICC pdicc){
  if(!pdicc) return;
  if(pdicc->tabla)
    free(pdicc->tabla);
  free(pdicc);
}

int inserta_diccionario(PDICC pdicc, int clave){
  int i, buff, counter = 0;
  if(!pdicc || clave <= 0)
    return ERR;
  if(pdicc->n_datos == pdicc->tamanio)
    return ERR;
  pdicc->tabla[pdicc->n_datos] = clave;
  pdicc->n_datos++;
  if(pdicc->orden == ORDENADO){
    buff = pdicc->tabla[pdicc->n_datos-1];
    i = pdicc->n_datos - 2;
    while(i >= 0 && pdicc->tabla[i] > buff){
      pdicc->tabla[i + 1] = pdicc->tabla[i];
      i--;
      counter++;
    }
    if(counter > 0)
      pdicc->tabla[i+1] = buff;
  }
  return counter;
}

int insercion_masiva_diccionario(PDICC pdicc, int *claves, int n_claves){
	int j, counter, cerror;
  if(!pdicc || !claves || n_claves <= 0 || ((pdicc->n_datos + n_claves) > pdicc->tamanio)){
    return ERR;
  }
  for(j = 0, counter = 0, cerror = 0; j < n_claves ; j++){
    cerror += inserta_diccionario(pdicc, claves[j]);
    if(cerror == ERR){
      return ERR;
    }
    counter += cerror;
  }
  return counter;
}


int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo){
  int counter;
  if(!pdicc || clave <= 0 || !metodo)
    return ERR;
  counter = metodo(pdicc->tabla, 0, pdicc->n_datos - 1, clave, ppos);
  return counter;
}

void imprime_diccionario(PDICC pdicc){
int i;
  if(!pdicc) return;
  printf("%d:%d:%d[ ", pdicc->tamanio, pdicc->n_datos, pdicc->orden);
  for (i = 0; i < pdicc->n_datos; i++) {
    printf("%d ", pdicc->tabla[i]);
  }
  printf(" ]\n");
}

/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla,int P,int U,int clave,int *ppos){

  int counter = 0, error, medio;

  if(!tabla || P > U){
    return NO_ENCONTRADO;
  }

  medio = (P+U)/2;
  if(tabla[medio] == clave){
      *ppos = medio + 1;
      return 1;
  }

  if(tabla[medio] < clave){
    P = medio + 1;
    /*U se queda igual*/
    counter++;
  }
  else{
    /*P se queda igual*/
    U = medio - 1;
    counter++;
  }

  error = bbin(tabla, P, U, clave, ppos);
  if(error == NO_ENCONTRADO){
    return NO_ENCONTRADO;
  }
  counter += error;
  return counter;
}

int blin(int *tabla,int P,int U,int clave,int *ppos){
  int i, counter = 0;
  if(!tabla || P < 0 || U < P || clave <= 0){
    return ERR;
  }
  for(i = P, counter = 0; i <= U && tabla[i] != clave; i++, counter++);
  if(i > U){
    return NO_ENCONTRADO;
  }
  *ppos = i + 1;
  counter++;
  return counter;
}

int blin_auto(int *tabla,int P,int U,int clave,int *ppos){
  int i, counter, buff;
  if(!tabla || P < 0 || U < P || clave <= 0)
    return ERR;
  for(i = P, counter = 0; i <= U && tabla[i] != clave; i++, counter++);
  if(i > U)
    return NO_ENCONTRADO;
  if(i == P){
    *ppos = 1;
    return 1;
  }
  buff = tabla[i];
  tabla[i] = tabla[i-1];
  tabla[i-1] = buff;
  *ppos = i;
  counter++;
  return counter;
}
