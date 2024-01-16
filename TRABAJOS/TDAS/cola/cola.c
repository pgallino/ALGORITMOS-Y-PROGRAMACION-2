#include "cola.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo nodo_t;

struct nodo {

    void* dato;
    nodo_t* prox;

};

struct cola {

    nodo_t *primero;
    nodo_t *ultimo;

};

nodo_t *nodo_crear(void* dato_usuario) {

    nodo_t *nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL) {
        return NULL;
    }

    nodo -> dato = dato_usuario;
    nodo -> prox = NULL;
    return nodo;
}

void nodo_destruir(nodo_t *nodo) {

    free(nodo);
}

cola_t *cola_crear(void) {

    cola_t *cola = malloc(sizeof(cola_t));

    if (cola == NULL) {
        return NULL;
    }

    cola -> primero = NULL;
    cola -> ultimo = cola -> primero;
    return cola;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {

    while (!cola_esta_vacia(cola)) {

        void* dato = cola_desencolar(cola);

        if (destruir_dato) destruir_dato(dato);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola) {

    return cola -> primero == NULL;
}

bool cola_encolar(cola_t *cola, void *valor) {

    nodo_t *nodo_nuevo = nodo_crear(valor);

    if (!nodo_nuevo) return false;

    if (cola_esta_vacia(cola)) {
        cola -> primero = nodo_nuevo;
    } else {
        (cola -> ultimo) -> prox = nodo_nuevo;
    }
    cola -> ultimo = nodo_nuevo;
    return true;
}

void *cola_ver_primero(const cola_t *cola) {

    return cola_esta_vacia(cola) ? NULL : (cola -> primero) -> dato;
}

void *cola_desencolar(cola_t *cola) {

    if (cola_esta_vacia(cola)) return cola -> primero;
    
    void* dato = cola_ver_primero(cola);
    nodo_t *nodo = cola -> primero;
    cola -> primero = nodo -> prox;

    nodo_destruir(nodo); //destruyo el nodo que se crea al encolar, porque al desencolar se perdería memoria
    return dato;
}