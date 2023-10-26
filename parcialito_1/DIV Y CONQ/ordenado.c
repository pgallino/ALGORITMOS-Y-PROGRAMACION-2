#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

bool _arreglo_ordenado(int arreglo[], size_t desde, size_t hasta) {
    if (desde == hasta) {
        return true;
    }

    size_t medio = (desde + hasta) / 2;
    bool ord_izq = _arreglo_ordenado(arreglo, desde, medio);
    bool ord_der = _arreglo_ordenado(arreglo, medio + 1, hasta);
    bool ord_uni = arreglo[medio] <= arreglo[medio + 1];

    return ord_izq && ord_uni && ord_der;
}

bool arreglo_ordenado(int arr[], size_t n) {
    return _arreglo_ordenado(arr, 0, n);
}