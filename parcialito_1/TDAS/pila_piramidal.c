#include "main.h" // No borrar
#include "pila.h"

bool pila_es_piramidal(pila_t* pila) {

    int sentinela = 0;
    
    pila_t *pila_aux = pila_crear();

    int* anterior = pila_desapilar(pila);

    pila_apilar(pila_aux, anterior);

    while (pila_esta_vacia(pila) == false) {

        int* actual = pila_desapilar(pila);

        pila_apilar(pila_aux, actual);

        if (*anterior >= *actual) {

            sentinela = 1;
        }

        anterior = actual;
    }

    while (pila_esta_vacia(pila_aux) == false) {

        pila_apilar(pila, pila_desapilar(pila_aux));
    }

    pila_destruir(pila_aux);

    if (sentinela == 1) {

        return false;

    } else if (sentinela == 0) {
        return true;
    }
}