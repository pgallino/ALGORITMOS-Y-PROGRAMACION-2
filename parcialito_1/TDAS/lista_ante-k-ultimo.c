#include "lista.h"
#include "lista_struct.h"

void* lista_ante_k_ultimo(lista_t* lista, size_t k) {
    
    nodo_t *actual = lista -> primero;

    while (actual != NULL) {

        nodo_t *actual_aux = actual;

        size_t contador = 0;

        while (contador < k) {

            actual_aux = actual_aux -> prox;
            contador ++;
        }

        if (actual_aux == NULL) {

            break;
        }

        actual = actual -> prox;
    
    }

    return actual -> dato;
}