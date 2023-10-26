#include "cola.h"
#include "cola_multi.h"

void** cola_multiprimeros(cola_t* cola, size_t k) {

    void** resultado = malloc(sizeof(void*) * k);
    size_t contador = 0;

    while (contador < k) {

        if (cola_esta_vacia(cola) == false) {

            resultado[contador] = cola_desencolar(cola);

        } else {

            resultado[contador] = NULL;
        }

        contador ++;
    }

    return resultado;
}