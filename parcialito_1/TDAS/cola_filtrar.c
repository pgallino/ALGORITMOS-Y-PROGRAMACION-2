#include "cola.h"

void cola_filtrar(cola_t* cola, bool (*filtro)(void*)) {
    
    cola_t *aux = cola_crear();

    while  (cola_esta_vacia(cola) == false) {

        void* elemento = cola_desencolar(cola);

        if (filtro(elemento) == true) {

            cola_encolar(aux, elemento);
        }
    }

    while (cola_esta_vacia(aux) == false) {

        cola_encolar(cola, cola_desencolar(aux)); 
    }

    cola_destruir(aux, NULL);
}