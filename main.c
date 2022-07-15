/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 4
 * AUTHOR 1: Daniela A Cisneros Sande LOGIN 1: d.cisneross
 * GROUP: 4.1
 * DATE: 01 / 07 / 22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255
#define N 20

void new(tProductId pd, tUserId userId, tProductCategory prodCategory, tProductPrice price, tList *L) {
    char category[N];
    tItemL producto;
    tStack *pujasP;
    pujasP = &producto.bidStack;
    tPosL p;
    p = (findItem(pd, *L));

    if (p == LNULL) {
        strcpy(producto.productId, pd);
        strcpy(producto.seller, userId);

        if (prodCategory == book) {
            producto.productCategory = book;
            strcpy(category, "book");
        } else {
            producto.productCategory = painting;
            strcpy(category, "painting");
        }
        producto.productPrice = price;
        createEmptyStack(pujasP);
        producto.bidCounter = 0;

        if (insertItem(producto, L) == true) {
            printf("* New: product %s seller %s category %s price %.2f \n", pd, userId, category, price);
        } else {
            printf("+ Error: New not possible\n");
        }
    } else {
        printf("+ Error: New not possible\n");
    }
}

/*
  *************************************** FUNCION NEW *********************************************

 * OBJETIVO: Alta de un nuevo producto con sus caracteristicas.
 * ENTRADA: -tProductId: Identificador del producto.
 *          -tUserId: Identificador del usuario.
 *          -tProductCategory: Categoria del producto (book, painting).
 *          -tProductPrice: Precio del producto.
 *          -tList: lista ordenada de productos.
 * SALIDA: La lista pasada por referencia con el nuevo producto introducido.
 * PRECD: La lista debe estar creada.
 * POSC: El producto estara agregado y ademas de esto, si ya existian productos, pueden haber variado de posicion.
*/

void delete(tProductId prodId, tList *L) {
    tItemL producto;
    char category[N];
    tStack *pujasP;
    tPosL p;
    p = findItem(prodId, *L);

    if (p != LNULL) {
        producto = getItem(p, *L);
        pujasP = &producto.bidStack;

        if (producto.productCategory == book) {
            producto.productCategory = book;
            strcpy(category, "book");
        } else {
            producto.productCategory = painting;
            strcpy(category, "painting");
        }
        while (!isEmptyStack(*pujasP)) {
            pop(pujasP);
        }
        deleteAtPosition(p, L);
        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n", prodId, producto.seller, category,
               producto.productPrice, producto.bidCounter);
    } else {
        printf("+ Error: Delete not possible\n");
    }
}

/*
************************************* FUNCION DELETE ******************************************

 * OBJETIVO: Baja un producto de la lista (todas sus caracteristicas se eliminaran).
 * ENTRADA: -tProductId: Identificador del producto.
 *          -tList: Lista de productos.
 * SALIDA: La lista pasada por referencia, sin el producto.
 * PRECD: La lista y la pila deben estar creadas.
 * POSC: Los productos posteriores pueden haber variado de posicion.
*/

void bid(tProductId prodId, tUserId userId, tProductPrice price, tList *L) {
    tItemL producto;
    tItemS puja;
    tStack *pujasP;
    char category[N];
    tPosL p;
    p = findItem(prodId, *L);

    if (p != LNULL) {
        producto = getItem(p, *L);
        pujasP = &producto.bidStack;
        if (!isEmptyStack(pujasP)){
            puja = peek(*pujasP);
            if ((price > puja.productPrice) && (price > producto.productPrice) &&
                (strcmp(producto.seller, userId) != 0)) {
                if (producto.productCategory == book) {
                    producto.productCategory = book;
                    strcpy(category, "book");
                } else {
                    producto.productCategory = painting;
                    strcpy(category, "painting");
                }
                puja.productPrice = price;
                strcpy(puja.bidder, userId);
                if (push(puja, pujasP)) {
                    producto.bidCounter++;
                    updateItem(producto, p, L);
                    printf("* Bid: product %s bidder %s category %s price %.2f bids %d\n", prodId, puja.bidder, category,
                           puja.productPrice, producto.bidCounter);
                } else {
                    printf("+ Error: Bid not possible\n");
                }
            } else {
                printf("+ Error: Bid not possible\n");
            }
        } else {
            printf("+ Error: Bid not possible\n");
        }
    } else {
        printf("+ Error: Bid not possible\n");
    }
}

/*
  *************************************** FUNCION BID *********************************************

 * OBJETIVO: Puja por un determinado producto.
 * ENTRADA: -tProductId: Identificador del producto.
 *          -tUserId: Identificador del usuario.
 *          -tProductPrice: Precio del producto.
 *          -tList: Lista de productos.
 * SALIDA: La lista pasada por referencia con el precio de la puja actualizado.
 * PRECD: La lista y el stack deben existir.
*/

void award(tProductId prodId, tList *L) {
    tItemL producto;
    tItemS puja;
    tStack *pujasP;
    tPosL p;
    char category[N];
    p = findItem(prodId, *L);

    if (p != LNULL) {
        producto = getItem(p, *L);
        pujasP = &producto.bidStack;
        if (!isEmptyStack(*pujasP)) {
            puja = peek(*pujasP);
            while (!isEmptyStack(*pujasP)) { //Vaciamos el stack
                pop(pujasP);
            }
            if (producto.productCategory == book) {
                producto.productCategory = book;
                strcpy(category, "book");
            } else {
                producto.productCategory = painting;
                strcpy(category, "painting");
            }
            printf("* Award: product %s bidder %s category %s price %.2f\n", prodId, puja.bidder, category,
                   puja.productPrice);
            deleteAtPosition(p, L);
        } else {
            printf("+ Error: Award not possible\n");
        }
    } else {
        printf("+ Error: Award not possible\n");
    }
}

/*
  *************************************** FUNCION AWARD *********************************************
 * OBJETIVO: Asignar el ganador de una puja.
 * ENTRADA: -tProductId: Identificador del producto.
 *          -tList: Lista de productos.
 * SALIDA: La lista pasada por referencia actualizada (sin el producto que se ha vendido).
 * PRECD: La lista y la pila deben existir.
*/

void withdraw(tProductId prodId, tUserId userId, tList *L) {
    tItemL producto;
    tPosL p;
    char category[N];
    tStack *pujasP;
    tItemS puja;
    p = findItem(prodId, *L);

    if (p != LNULL) {
        producto = getItem(p, *L);
        pujasP = &producto.bidStack;
        puja = peek(*pujasP);
        if (!isEmptyStack(*pujasP) && (strcmp(puja.bidder, userId) == 0)) {
            if (producto.productCategory == book) {
                producto.productCategory = book;
                strcpy(category, "book");
            } else {
                producto.productCategory = painting;
                strcpy(category, "painting");
            }
            printf("* Withdraw: product %s bidder %s category %s price %.2f bids %d\n", prodId, puja.bidder, category,
                   puja.productPrice, producto.bidCounter);
            pop(pujasP);
            producto.bidCounter--;
            updateItem(producto, p, L);
        } else {
            printf("+ Error: Withdraw not possible\n");
        }
    } else {
        printf("+ Error: Withdraw not possible\n");
    }
}

/*
  *************************************** FUNCION WITHDRAW *********************************************
 * OBJETIVO: Retirada de la máxima puja actual del producto.
 * ENTRADA: -tProductId: Identificador del producto.
 *          -tUserId: Identificador del usuario.
 *          -tList: Lista de productos.
 * SALIDA: La lista pasada por referencia con el contador de pujas del producto actualizado.
 * PRECD: La lista y la pila deben existir.
*/

void Remove(tList *L) {
    char category[N];
    tItemL producto;
    tPosL p, nextp;
    int contBorrados = 0;  //Contador para saber si borramos o no algo de la lista

    if (!isEmptyList(*L)) {
        p = first(*L);
        while (p != LNULL) {
            producto = getItem(p, *L);
            nextp = next(p, *L);
            if (producto.bidCounter == 0) {
                if (producto.productCategory == book) {
                    producto.productCategory = book;
                    strcpy(category, "book");
                } else {
                    producto.productCategory = painting;
                    strcpy(category, "painting");
                }
                printf("Removing product %s seller %s category %s price %.2f bids %d\n", producto.productId,
                       producto.seller, category, producto.productPrice, producto.bidCounter);
                deleteAtPosition(p, L);
                contBorrados++;
            }
            p = nextp;
        }
        if (contBorrados == 0) {
            printf("+ Error: Remove not possible\n");
        }
    } else {
        printf("+ Error: Remove not possible\n");
    }
}

/*
  *************************************** FUNCION REMOVE *********************************************
 * OBJETIVO: Elimina los productos sin pujas.
 * ENTRADA: -tList: Lista de productos.
 * SALIDA: La lista sin los productos indicados.
 * PRECD: La lista y la pila deben existir.
*/

void stats(tList L) {
    int books = 0, paintings = 0;  //contadores de categoria book y categoria painting, inicializadas a 0
    float priceBooks = 0, pricePaintings = 0; //acumuladores de los precios
    tItemL producto;
    tPosL p;
    tItemS puja;
    tStack *pujasP;
    float increase = 0, d_precio, price = 0, top_price = 0, increaseActual;
    bool hay_bids = false;
    char category[N], product[N], seller[N], categoryB[N], bidder[N];

    if (!isEmptyList(L)) {
        p = first(L);
        while (p != LNULL) {
            producto = getItem(p, L);
            pujasP = &producto.bidStack;

            if (producto.productCategory == book) {
                strcpy(category, "book");
                books++;
                priceBooks += producto.productPrice;
            } else { //Si no es "book" entonces sera "painting"
                strcpy(category, "painting");
                paintings++;
                pricePaintings += producto.productPrice;
            }
            if (!isEmptyStack(*pujasP)) {
                puja = peek(*pujasP);
                hay_bids = true;
                d_precio = puja.productPrice - producto.productPrice;
                increaseActual = (d_precio / producto.productPrice) * 100;
                if (increase < increaseActual) {
                    increase = increaseActual;
                    strcpy(product, producto.productId);
                    strcpy(seller, producto.seller);
                    strcpy(categoryB, category);
                    price = producto.productPrice;
                    strcpy(bidder, puja.bidder);
                    top_price = puja.productPrice;
                }
                printf("Product %s seller %s category %s price %.2f bids %d top bidder %s\n", producto.productId,
                       producto.seller, category, producto.productPrice, producto.bidCounter, puja.bidder);
            } else {
                printf("Product %s seller %s category %s price %.2f. No bids\n", producto.productId,
                       producto.seller, category, producto.productPrice);
            }
            p = next(p, L);
        }
        printf("\nCategory  Products    Price  Average\n"
               "Book      %8d %8.2f %8.2f\n"
               "Painting  %8d %8.2f %8.2f\n", books, priceBooks, books == 0 ? 0 : (priceBooks / (float) books),
               paintings, pricePaintings, paintings == 0 ? 0 : (pricePaintings / (float) paintings));
        if (hay_bids) {
            printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
                   product, seller, categoryB, price, bidder, top_price, increase);
        } else {
            printf("Top bid not possible\n");
        }
    } else {
        printf("+ Error: Stats not possible\n");
    }
}

/*
  *************************************** FUNCION STATS *******************************************

 * OBJETIVO: Mostrar el listado de productos actuales y sus datos.
 * ENTRADA: -tList: Lista de productos.
 * SALIDA: No hay parametros de salida (ni por referencia) ya que la lista no se modifica y solo se muestran sus datos.
*/

void invalidateBids(tList *L) {
    char category[N];
    tItemL producto;
    tStack *pujasP;
    tPosL p, nextp;
    int contBorrados = 0;
    float avgBids = 0, contProductos = 0;

    if (!isEmptyList(*L)) {
        p = first(*L);
        while (p != LNULL) {
            producto = getItem(p, *L);
            contProductos++;
            avgBids += producto.bidCounter;
            p = next(p, *L);
        }
        avgBids = (avgBids / contProductos);
    }

    if (!isEmptyList(*L)) {
        p = first(*L);
        while (p != LNULL) {
            producto = getItem(p, *L);
            pujasP = &producto.bidStack;
            nextp = next(p, *L);
            if (producto.bidCounter > (avgBids * 2)) {
                if (producto.productCategory == book) {
                    producto.productCategory = book;
                    strcpy(category, "book");
                } else {
                    producto.productCategory = painting;
                    strcpy(category, "painting");
                }
                printf("* InvalidateBids: product %s seller %s category %s price %.2f bids %d average bids %.2f\n",
                       producto.productId, producto.seller, category, producto.productPrice, producto.bidCounter,
                       avgBids);
                while(!isEmptyStack(*pujasP)){
                    pop(pujasP);
                    producto.bidCounter--;
                }
                updateItem(producto, p, L);
                contBorrados++;
            }
            p = nextp;
        }
        if (contBorrados == 0) {
            printf("+ Error: InvalidateBids not possible\n");
        }
    } else {
        printf("+ Error: InvalidateBids not possible\n");
    }
}

/*
  *************************************** FUNCION INVALIDATEBIDS *******************************************

 * OBJETIVO: Elimina las pujas fraudulentas.
 * ENTRADA: -tList: Lista de productos.
 * SALIDA: La lista sin pujas fraudulentas.
 * PRECD: Lista creada.
*/

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4,
                    tList *L) {

    printf("********************\n");
    switch (command) {
        case 'N':
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3,
                   param4);
            if (strcmp(param3, "book") == 0) {
                new(param1, param2, book, atof(param4), L);
            } else if (strcmp(param3, "painting") == 0) {
                new(param1, param2, painting, atof(param4), L);
            }
            break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            stats(*L);
            break;
        case 'B':
            printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            bid(param1, param2, atof(param3), L);
            break;
        case 'D':
            printf("%s %c: product %s \n", commandNumber, command, param1);
            delete(param1, L);
            break;
        case 'A':
            printf("%s %c: product %s \n", commandNumber, command, param1);
            award(param1, L);
            break;
        case 'W':
            printf("%s %c: product %s bidder %s \n", commandNumber, command, param1, param2);
            withdraw(param1, param2, L);
            break;
        case 'R':
            printf("%s %c\n", commandNumber, command);
            Remove(L);
            break;
        case 'I':
            printf("%s %c\n", commandNumber, command);
            invalidateBids(L);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];
    tList L;
    createEmptyList(&L);

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, &L);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}
