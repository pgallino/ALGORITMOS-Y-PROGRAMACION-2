#include "pila.h"
#include <stdlib.h>
#define MIN_LARGO 20
#define COEF_AUMENTO 2
#define COEF_DISMINUCION 2
#define COEF_MAX_EXCESO 4
#include <stdio.h>

/* Definición del struct pila proporcionado por la cátedra.
*/
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

pila_t* pila_crear(void) {
    pila_t* pila = malloc(sizeof(pila_t));
    if (pila == NULL) return NULL;
    pila->cantidad = 0;
    pila->capacidad = MIN_LARGO;
    pila->datos = malloc(sizeof(void*) * pila->capacidad);
    return pila;
}

void pila_destruir(pila_t *pila) {
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
    return pila->cantidad == 0;
}

void *pila_ver_tope(const pila_t *pila) {
    if (pila_esta_vacia(pila)) return NULL;
    return pila->datos[pila->cantidad - 1];
}

bool _pila_redimensionar(pila_t* pila, size_t nuevo_tam) {
    printf("%zu, %zu, %zu \n", nuevo_tam / 8, pila->cantidad, pila->capacidad);
    void* aux = realloc(pila->datos, nuevo_tam);
    if (aux == NULL) return false;
    pila->datos = aux;
    pila->capacidad = nuevo_tam / sizeof(void*);
    return true;
}

bool pila_apilar(pila_t *pila, void *valor) {
    if (pila->cantidad == pila->capacidad) {
        bool se_redimensiono = _pila_redimensionar(pila, sizeof(void*) * pila->capacidad * COEF_AUMENTO);
        if (se_redimensiono == false) return false;
    }
    pila->datos[pila->cantidad++] = valor;
    return true;
}

void *pila_desapilar(pila_t *pila) {
    if (pila_esta_vacia(pila)) return NULL;
    if ((pila->cantidad * COEF_MAX_EXCESO <= pila->capacidad) && (pila->capacidad > MIN_LARGO)) {
        _pila_redimensionar(pila, (sizeof(void*) * pila->capacidad) / COEF_DISMINUCION);
    }
    return pila->datos[--pila->cantidad];
}