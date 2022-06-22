/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 4
 * AUTHOR 1: Daniela A Cisneros Sande LOGIN 1: d.cisneross
 * GROUP: 4.1
 * DATE: 01 / 07 / 22
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SMAX 25
#define SNULL -1

typedef int tPosS;

typedef struct {
    tUserId bidder;
    tProductPrice productPrice;
} tItemS;

typedef struct {
    tItemS data[SMAX];
    tPosS top;
} tStack;

void createEmptyStack(tStack *stack);

/*
 * OBJETIVO: crea una pila vacia.
 * ENTRADA: -tStack: pila de pujas.
 * POSTCD: la pila no tiene elementos.
 * SALIDA: posicion del producto indicado.
*/

bool isEmptyStack(tStack stack);

/*
 * OBJETIVO: determina si una pila esta vacia.
 * ENTRADA: -tStack: pila de pujas.
 * SALIDA: un valor de tipo bool donde aparece:
 *              Verdadero: si esta vacia.
 *              Falso: en caso contrario.
*/

bool push(tItemS d, tStack *stack);

/*
 * OBJETIVO: inserta un elemento en la cima de la pila.
 * ENTRADA: -tItemS: conjunto de datos de una puja de la pila.
            -tStack: pila de pujas.
 * SALIDA: un valor de tipo bool donde aparece:
 *              Verdadero: si el elemento fue apilado.
 *              Falso: en caso contrario.
*/

void pop(tStack *stack);

/*
 * OBJETIVO: elimina de la pila el elemento situado en la cima.
 * ENTRADA: -tStack: pila de pujas.
 * SALIDA: la pila sin dicho elemento.
 * PRECD: la pila no esta vacia.
*/

tItemS peek(tStack stack);

/*
 * OBJETIVO: recupera el elemento de la cima sin eliminarlo.
 * ENTRADA: -tStack: pila de pujas.
 * SALIDA: el elemento de la cima.
 * PRECD: la pila no esta vacia.
*/

#endif