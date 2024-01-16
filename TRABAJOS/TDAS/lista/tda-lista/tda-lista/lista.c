#include "lista.h"
#include <stdlib.h>

typedef struct nodo nodo_t;

struct nodo {
    void* dato;
    nodo_t* prox;
};

struct lista {
    nodo_t* prim;
    nodo_t* ult;
    size_t largo;
};

nodo_t* nodo_crear(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

lista_t* lista_crear() {
    lista_t* lista = malloc(sizeof(lista_t));
    if (lista == NULL) return NULL;
    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
    return lista->prim == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t* nodo = nodo_crear(dato);
    if (nodo == NULL) return NULL;
    nodo->prox = lista->prim;
    if(lista_esta_vacia(lista)) lista->ult = nodo;
    lista->prim = nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t* nodo = nodo_crear(dato);
    if (nodo == NULL) return NULL;
    if (lista_esta_vacia(lista)){
        lista->prim = nodo;
    }
    else {
        lista->ult->prox = nodo;
    }
    lista->ult = nodo;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    void* dato = lista->prim->dato;
    nodo_t* nuevo_prim = lista->prim->prox;
    free(lista->prim);
    lista->prim = nuevo_prim;
    if(lista->prim == NULL) lista->ult = NULL;
    lista->largo--;
    return dato;
}

void *lista_ver_primero(const lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    while (!lista_esta_vacia(lista)) {
        void* eliminado = lista_borrar_primero(lista);
        if (destruir_dato != NULL) {
            destruir_dato(eliminado);
        }
    }
    free(lista);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    nodo_t* act = lista->prim;
    while(!(act == NULL) && visitar(act->dato, extra)) {
        act = act->prox;
    }
}

struct lista_iter {
    nodo_t* ant;
    nodo_t* act;
    lista_t* lista;
};

lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (iter == NULL) return NULL;
    iter->lista = lista;
    iter->ant = NULL;
    iter->act = lista->prim;
    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    if (iter->act == NULL) return false;
    iter->ant = iter->act;
    iter->act = iter->act->prox;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (iter->act == NULL || lista_esta_vacia(iter->lista)) return NULL;
    return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    return iter->act == NULL;
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t* nodo = nodo_crear(dato);
    if (nodo == NULL) return false;
    nodo->prox = iter->act;
    if (iter->ant == NULL) {
        iter->lista->prim = nodo;
    }
    else {
        iter->ant->prox = nodo;
    }
    if (iter->act == NULL) iter->lista->ult = nodo;
    iter->act = nodo;
    iter->lista->largo++;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
    if (iter->act == NULL || lista_esta_vacia(iter->lista)) return NULL;
    if (iter->ant == NULL){
        iter->lista->prim = iter->act->prox;
    }
    else {
        iter->ant->prox = iter->act->prox;
        if (iter->act->prox == NULL){
            iter->lista->ult = iter->ant;
        }
    }
    void* dato = iter->act->dato;
    void* act_anterior = iter->act;
    iter->act = iter->act->prox;
    free(act_anterior);
    iter->lista->largo--;
    return dato;
}