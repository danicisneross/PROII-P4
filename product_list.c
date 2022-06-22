/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 4
 * AUTHOR 1: Daniela A Cisneros Sande LOGIN 1: d.cisneross
 * GROUP: 4.1
 * DATE: 01 / 07 / 22
 */

#include "types.h"
#include "stdbool.h"
#include "product_list.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void createEmptyList(tList *L) {
    *L = LNULL;
}

bool isEmptyList(tList L) {
    return L == LNULL;
}

tPosL first(tList L) {
    return L;
}

tPosL last(tList L) {
    tPosL p;

    for (p = L; p->next != LNULL; p = p->next);
    return p;
}

tPosL next(tPosL p, tList L) {
    return p->next;
}

tPosL previous(tPosL p, tList L) {
    tPosL i;

    if (p == L) {
        return LNULL;
    } else {
        for (i = L; i->next != p; i = i->next);
        return i;
    }
}

bool createNode(tPosL *p) {
    *p = malloc(sizeof(**p));
    return *p != LNULL;
}

tPosL findPosition(tItemL d, tList L) {
    tPosL p;
    p = L;

    if (!isEmptyList(L)) {
        while ((p->next != LNULL) && (strcmp((p->next->data.productId), d.productId) < 0)) {
            p = p->next;
        }
        return p;
    }
    return LNULL;
}

bool insertItem(tItemL d, tList *L) {
    tPosL p, i;

    if (!createNode(&p)) {
        return false;
    } else {
        p->data = d;
        p->next = LNULL;
        if (*L == LNULL) { //La lista esta vacia
            *L = p;
        } else if (strcmp((*L)->data.productId, d.productId) > 0) { // Ultima posicion
            p->next = *L;
            *L = p;
        } else {
            i = findPosition(d, *L);
            p->next = i->next;
            i->next = p;
        }
        return true;
    }
}

//Violación de la poscondición de deleteAtPosition.
//PD: las posiciones de los elementos de la lista posteriores a la
//           posicion eliminada pueden haber variado.

void deleteAtPosition(tPosL p, tList *L) {
    tPosL i;

    if (!isEmptyList(*L)) {
        if (p == *L) { // borrar primer elemento
            *L = (*L)->next;
        } else if (p->next == LNULL) { // eliminar última posicion
            i = previous(p, *L);
            i->next = LNULL;
        } else { // eliminar posición intermedia
            i = p->next;
            p->data = i->data;
            p->next = i->next;
            p = i;
        }
        free(p);
    }
}

tItemL getItem(tPosL p, tList L) {
    return p->data;
}

void updateItem(tItemL d, tPosL p, tList *L) {
    if (!isEmptyList(*L)) {
        p->data = d;
    }
}

tPosL findItem(tProductId pd, tList L) {
    tPosL p;

    if (!isEmptyList(L)) {
        for (p = L; ((p != LNULL) && (strcmp(p->data.productId, pd)) < 0); p = p->next);
        if (p != LNULL && (strcmp(p->data.productId, pd) == 0)) {
            return p;
        } else {
            return LNULL;
        }
    }
    return LNULL;
}