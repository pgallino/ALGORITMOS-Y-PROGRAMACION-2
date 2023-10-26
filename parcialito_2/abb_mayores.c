#include "abb.h"
#include "lista.h"
#include "abb_struct.h"

void _abb_mayores(abb_nodo_t* nodo, const char* clave, lista_t* mayores, abb_comparar_clave_t cmp) {
    if (nodo == NULL) {
        return;
    }
    if (cmp(nodo->clave, clave) > 0) {
        _abb_mayores(nodo->izq, clave, mayores, cmp);
        lista_insertar_primero(mayores, nodo->clave);
    }
    _abb_mayores(nodo->der, clave, mayores, cmp);
}

lista_t* abb_mayores(const abb_t* abb, const char* clave) {
    lista_t* mayores = lista_crear();
    abb_nodo_t* nodo = abb->raiz;
    if (!mayores) {
        return NULL;
    }
    _abb_mayores(nodo, clave, mayores, abb->cmp);
    return mayores;
}