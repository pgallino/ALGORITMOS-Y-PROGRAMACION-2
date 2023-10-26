#include "ej.h"

void swap(int* arreglo, size_t inicio, size_t cant) {
    for (size_t i = inicio; i<inicio+cant; i++) {
        int aux = arreglo[i];
        arreglo[i] = arreglo[i+cant];
        arreglo[i+cant] = aux;
    }

}

void _alternar(int* arreglo, size_t inicio, size_t fin) {

    size_t cant = fin-inicio;

    if (cant == 2) {
        return;
    }

    swap(arreglo, inicio + cant/4, cant/4);

    _alternar(arreglo, 0, cant/2);
    _alternar(arreglo,cant/2, cant);

    
}

void alternar(int* arreglo, size_t n) {
    _alternar(arreglo, 0, 2*n);
}