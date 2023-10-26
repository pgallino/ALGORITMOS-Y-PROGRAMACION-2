"""Implementar un algoritmo en C que reciba un arreglo de enteros de tamaño n, ordenado ascendentemente 
y sin elementos repetidos, y determine en O(log n) si es mágico. 
Un arreglo es mágico si existe algún valor i tal que 0 <= i y arr[i] = i. Justificar el orden del algoritmo.

Ejemplos:

A = [ -3, 0, 1, 3, 7, 9 ] es mágico porque A[3] = 3.

B = [ 1, 2, 4, 6, 7, 9 ] no es mágico porque B[i] != i para todo i."""

bool _es_magico(int* arr, size_t inicio, size_t final) {

    if (inicio >= final) return false;

    size_t medio = (inicio + final) / 2;

    if (arr[medio] == medio) return true;

    if (arr[medio] > medio) return _es_magico(arr, inicio, medio-1);

    if (arr[medio] < medio) return _es_magico(arr, medio+1, final);
}

bool es_magico(int* arr, size_t largo) {
    return _es_magico(arr, 0, largo);
}

