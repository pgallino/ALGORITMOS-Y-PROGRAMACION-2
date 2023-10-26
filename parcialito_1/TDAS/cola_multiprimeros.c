#include "cola.h"
#include "cola_struct.h"
#include <stdlib.h>

void** cola_multiprimeros(const cola_t* cola, size_t k) {
    void** multi = malloc(sizeof(void*) * k);

    nodo_t* nodo = cola->prim;
    for (int i = 0; i < k; i++) {
        if (nodo != NULL) {
            multi[i] = nodo->dato;
            nodo = nodo->sig;
        } else {
            multi[i] = NULL;
        }
    }
    return multi;
}