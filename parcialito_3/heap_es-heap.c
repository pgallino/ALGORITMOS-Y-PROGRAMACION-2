// Implementar en lenguaje C una función recursiva con la firma bool es_heap(int arr[], size_t n). 
// Esta función debe devolver true o false de acuerdo a si el arreglo que recibe como parámetro 
// cumple la propiedad de heap (de mínimos).

#include "main.h"

bool _es_heap(int arr[], size_t padre, size_t tam) {
    if (padre*2+2 >= tam) return true;
    if (arr[padre] > arr[padre*2+1]) return false;
    if (arr[padre] > arr[padre*2+2]) return false;
    return _es_heap(arr, ++padre, tam);
}

bool es_heap(int arr[], size_t n) {
    return _es_heap(arr, 0, n);
}