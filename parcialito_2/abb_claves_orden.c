#include "abb.h"
#include "lista.h"
#include <stddef.h>
#include "abb_struct.h"

/* Implementar una primitiva para el ABB, que devuelva una lista con las claves del mismo,
ordenadas tal que si insertáramos las claves en un ABB vacío, 
dicho ABB tendría la misma estructura que el árbol original. */

void _abb_obtener_claves(abb_nodo_t* nodo, lista_t* lista) {

    if(!nodo) return;
    lista_insertar_ultimo(lista, nodo->clave);
    _abb_obtener_claves(nodo->izq, lista);
    _abb_obtener_claves(nodo->der, lista);
}

lista_t* abb_obtener_claves(abb_t* abb) {
    lista_t* lista = lista_crear();
    if(!lista) return NULL;
    _abb_obtener_claves(abb->raiz,lista);
    return lista;
}