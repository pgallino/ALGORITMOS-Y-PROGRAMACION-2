"""escribir en C una funcion k_merge que reciba k arreglos ordenados 
y devuelva uno nuevo con los elementos ordenados entre si
todos tienen longitud h"""

#include "heap.h"

"""con un heap de minimos primero saco el primero de todos los arreglos y despues voy desencolando del heap.
de donde saco encolo el siguiente a ese y repito todo"""
typedef struct minimo {
    void* dato;
    size_t subarreglo;
    size_t pos;
} minimo_t;

minimo_t* _crear__minimo(size_t pos, size_t subarreglo, void* dato) {
    minimo_t* minimo = malloc(sizeof(minimo_t*));
    if (!minimo) return NULL;
    minimo->dato = dato;
    minimo->subarreglo = subarreglo;
    minimo->pos = pos;
    return minimo;
}

void** k_merge(void*** arreglos, size_t k, size_t h) {
    void** resultado = malloc(k*h*sizeof(void*));
    heap* minimos = heap_crear(cmp);
    if (!minimos) return NULL;
    for(size_t i = 0; i<k; i++) {
        heap_encolar(minimos, _crear_minimo(0,i,arreglos[i][0]);
    } //hasta aca O(klogk)
    for (size_t i=0; !heap_esta_vacio(minimos); i++) {
        minimo_t* minimo = heap_desencolar(minimos);
        resultado[i] = minimo->dato;
        if (minimo->pos + 1 >= h) {
            free(minimo);
            continue;
        }
        size_t posicion = minimo->pos + 1;
        heap_encolar(minimos, _crear__minimo(posicion, minimo->subarreglo, arreglos[minimo->subarreglo][posicion]));
        free(minimo);
    } // O(h*klogk)
    heap_destruir(minimos, NULL);
    return resultado;
}