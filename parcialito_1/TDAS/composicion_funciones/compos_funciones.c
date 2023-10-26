#include "composicion_funciones.h"
#include <stdlib.h>
#include "pila.h"

// Agregar #include <tda.h> dependiendo del tda que necesites 

struct composicion {
    pila_t *datos;
    double valor;
    pila_t *aux;

};

composicion_t* composicion_crear() {

    composicion_t *composicion = malloc(sizeof(composicion_t));

    if (composicion == NULL) {
        return NULL;
    }

    composicion -> datos = pila_crear();

    if ((composicion -> datos) == NULL) {
        free(composicion);
        return NULL;
    }

    composicion -> aux = pila_crear();

    if ((composicion -> aux) == NULL) {
        free(composicion -> datos);
        free(composicion);
        return NULL;
    }


    return composicion;
    
}

void composicion_destruir(composicion_t* composicion) {
    // Completar
    free(composicion -> aux);
    free(composicion -> datos);
    free(composicion);
}

bool composicion_agregar_funcion(composicion_t* composicion, funcion_t f) {
    // Completar
    return pila_apilar(composicion -> datos, f);
}

double composicion_aplicar(composicion_t* composicion, double x) {
    // Completar

    composicion -> valor = x;


    while (pila_esta_vacia(composicion -> datos) == false) {


        funcion_t funcion = pila_desapilar(composicion -> datos);

        pila_apilar(composicion -> aux, funcion);
        
        (composicion -> valor) = funcion(composicion -> valor);

    }

    while (pila_esta_vacia(composicion -> aux) == false) {

        pila_apilar(composicion -> datos, pila_desapilar(composicion -> aux));
    
    }



    return (composicion -> valor);

}