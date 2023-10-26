// (★★★) Escribir una función en C que, 
// dado un arreglo de nn cadenas y un entero positivo k,
// devuelva una lista con las kk cadenas más largas.
// Se espera que el orden del algoritmo O(n+klogn). Justificar el orden.
#include "heap.h"

char** obtener_cadenas_mas_largas(char* cadenas, size_t tam, size_t k, cmp_func_t cmp) { //cmp es la de cadenas
    heap_t* heap = heap_crear_arr(cadenas, tam, cmp); //o(n)
    char** lista = malloc(k * sizeof(char*)); //o(n)
    if (!lista) return NULL;
    for(size_t i = 0; i<k;i++){                   //o(klogn)
        lista[i] = heap_desencolar(heap);
    }
    heap_destruir(heap, NULL); //o(n)
}

//otra forma es un heap de minimos e ir encolando con un tope k y 
//elijo si encolar o no dependiendo si es mayor al minimo del heap
//quedando o(nlogk)