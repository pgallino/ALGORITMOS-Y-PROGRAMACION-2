#define _POSIX_C_SOURCE 200809L
#include "pila.h"
#include "abb.h"
#include <stdlib.h>
#include <string.h>

typedef struct abb_nodo abb_nodo_t;

struct abb_nodo {
    abb_nodo_t* izq;
    abb_nodo_t* der;
    char *clave;
    void *dato;
};

struct abb {
    abb_nodo_t *raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t cant;
};

abb_nodo_t* _nodo_crear(const char* clave, void* dato) {
    abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
    if (!nodo) return NULL;
    nodo->clave = strdup(clave);
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t *abb = malloc(sizeof(abb_t));
    if (!abb) return NULL;
    abb->raiz = NULL;
    abb->cant = 0;
    abb->cmp = cmp;
    abb->destruir_dato = destruir_dato;
    return abb;
}

abb_nodo_t** _abb_buscar(abb_nodo_t** ref, abb_comparar_clave_t cmp, const char* clave) {
    abb_nodo_t* nodo = *ref;
    if (!cmp(clave, nodo->clave)) {
        return ref;
    }
    else if (cmp(clave, nodo->clave) > 0) {
        if (!nodo->der) return &nodo->der;
        return _abb_buscar(&nodo->der, cmp, clave);
    } else {
        if (!nodo->izq) return &nodo->izq;
        return _abb_buscar(&nodo->izq, cmp, clave);
    }
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    abb_nodo_t* nodo = _nodo_crear(clave, dato);
    if (!nodo) return false;
    arbol->cant++;
    if (!arbol->raiz) {
        arbol->raiz = nodo;
        return true;
    }
    abb_nodo_t** ref = _abb_buscar(&arbol->raiz, arbol->cmp, clave);
    if (*ref) {  // ya se encontraba la clave
        arbol->cant--;
        if (arbol->destruir_dato) arbol->destruir_dato((*ref)->dato);
        free(nodo->clave);
        free(nodo);
        (*ref)->dato = dato;
    } else *ref = nodo;
    return true;
}

abb_nodo_t* _realizar_reemplazo(abb_nodo_t* nodo) {
    abb_nodo_t** reemplazo = &(nodo->izq);
    while ((*reemplazo)->der) reemplazo = &(*reemplazo)->der;
    nodo->clave = (*reemplazo)->clave;
    nodo->dato = (*reemplazo)->dato;
    nodo = *reemplazo;
    *reemplazo = (*reemplazo)->izq ? (*reemplazo)->izq : NULL;
    return nodo;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    if (!arbol->cant) return NULL;
    abb_nodo_t** ref = _abb_buscar(&arbol->raiz, arbol->cmp, clave);
    abb_nodo_t* nodo = *ref;
    if (!nodo) return NULL;
    void* dato = nodo->dato;
    free(nodo->clave);

    if ((!nodo->izq && !nodo->der) || (nodo->izq && !nodo->der)) *ref = nodo->izq;
    else if (!nodo->izq && nodo->der) *ref = nodo->der;
    else nodo = _realizar_reemplazo(nodo);
    arbol->cant--;
    free(nodo);
    return dato;
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
    if (!arbol->cant) return NULL;
    abb_nodo_t* raiz = arbol->raiz;
    abb_nodo_t** ref = _abb_buscar(&raiz, arbol->cmp, clave);
    if ((*ref)) return (*ref)->dato;
    return NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    if (!arbol->cant) return false;
    abb_nodo_t* raiz = arbol->raiz;
    abb_nodo_t** ref = _abb_buscar(&raiz, arbol->cmp, clave);
    if ((*ref) && !arbol->cmp(clave, (*ref)->clave)) return true;
    return false;
}

size_t abb_cantidad(const abb_t *arbol) {
    return arbol->cant;
}

void _abb_destruir(abb_nodo_t* nodo, abb_destruir_dato_t destruir_dato) {
    if (!nodo) return;
    _abb_destruir(nodo->izq, destruir_dato);
    _abb_destruir(nodo->der, destruir_dato);
    if(destruir_dato) destruir_dato(nodo->dato);
    free(nodo->clave);
    free(nodo);
}

void abb_destruir(abb_t *arbol) {
    _abb_destruir(arbol->raiz, arbol->destruir_dato);
    free(arbol);
}

bool _abb_in_order(abb_nodo_t* act, bool visitar(const char *, void *, void *), void* extra) {
    if (!act) return true;
    bool izq = _abb_in_order(act->izq, visitar, extra);
    if (!izq) return false;
    if (!visitar(act->clave, act->dato, extra)) return false;
    return _abb_in_order(act->der, visitar, extra);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
    _abb_in_order(arbol->raiz, visitar, extra);
}


struct abb_iter {
    pila_t* pila;
};

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter) return NULL;
    iter->pila = pila_crear();
    if (!iter->pila) {
        free(iter);
        return NULL;
    }
    abb_nodo_t* nodo = arbol->raiz;
    while (nodo) {
        pila_apilar(iter->pila, nodo);
        nodo = nodo->izq;
    }
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) { //se recorre in order
    if (abb_iter_in_al_final(iter)) return false;
    abb_nodo_t* nodo = pila_desapilar(iter->pila);
    if (nodo->der){
        pila_apilar(iter->pila,nodo->der);
        nodo = nodo->der->izq;
        while (nodo) {
            pila_apilar(iter->pila, nodo);
            nodo = nodo->izq;
        }
    }
    return true;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
    return pila_esta_vacia(iter->pila);
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
    abb_nodo_t* nodo = pila_ver_tope(iter->pila);
    if (!nodo) return NULL;
    return nodo->clave;
}

void abb_iter_in_destruir(abb_iter_t* iter) {
    pila_destruir(iter->pila);
    free(iter);
}