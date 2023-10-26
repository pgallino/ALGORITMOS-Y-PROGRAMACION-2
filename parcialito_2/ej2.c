/* 3. Dada la siguiente estructura de lista, implementar una primitiva void* lista_borrar_ultimo(lista_t* lista), que
quite y devuelva el último elemento de la lista. 
En caso de que la lista esté vacía devuelve NULL. Indicar y justificar la
complejidad de la primitiva implementada.

typedef struct nodo_lista {
struct nodo_lista* prox;
void* dato;
} nodo_lista_t;

typedef struct lista {
nodo_lista_t* prim;
} lista_t; */

#include "lista.h"

typedef struct nodo_lista {
struct nodo_lista* prox;
void* dato;
} nodo_lista_t;

typedef struct lista {
nodo_lista_t* prim;
} lista_t;

void* lista_borrar_ultimo(lista_t* lista) {
    if (lista_esta_vacia(lista)) return NULL;
    nodo_lista_t* actual = lista->prim;
    nodo_lista_t* anterior = NULL;
    while (actual->prox) {
        anterior = actual;
        actual = actual->prox;
    }
    void* dato = actual->dato;
    if(actual == lista->prim) lista->prim = NULL; //solo habia un elemento.
    anterior->prox = NULL;
    free(actual); //libero el nodo que elimino.
    return dato;
}

//su complejidad es o(n) ya que no contamos con una referencia al ultimo nodo de la lista.
//Tenemos que recorrerla entera con un ciclo.