//ej2 enunciado

#include "heap.h"

void _calcular_combinaciones(int k, int* cant_comb, heap_t* heap) {
    
    int mas_grande = heap_desencolar(heap); //desencolo los dos mas grandes del heap
    int mas_grande_2 = heap_desencolar(heap):

    if (!mas_grande) return; //si es NULL corto la recursion (tal vez no hace falta, es por si el arreglo esta vacio)
    if (mas_grande <= k) return; //si es mas chico o igual a k corto la recursion

    if (mas_grande > k) {
        if (mas_grande_2 && mas_grande == mas_grande_2) { //si son iguales y mas grandes corto la recursion y marco -1
            cant_comb* = -1
            return
        }
        cant_comb* += 1;
        heap_encolar(2*mas_grande_2-mas_grande);
        _calcular_combinaciones(k, cant_comb, heap);
    }

}

int calcular_combinaciones(int arr[], int largo, int k) {

    int cant_comb = 0;
    heap_t* heap = crear_heap(cmp); //creo un heap de maximos con una funcion de comparacion de ints
    for(int i = 0; i<largo; i++){
        heap_encolar(arr[i]); //armo el heap con los elementos del arreglo
    }
    _calcular_combinaciones(k,&cant_comb,heap);
    heap_destruir(heap,NULL); //libero la memoria
    return cant_comb*

}

//complejidad: crear el heap es o(n); Primero encolo todo el arreglo, siendo largo * O(Logn) largo = n -> O(nlogn)
//luego por cada llamado recursivo desencolo 2 veces -> 2 * o(logn)
//en el caso de que el mas grande sea mayor, encolo una vez mas O(logn)
//y vuelve a llamar recursivamente

//la cantidad de llamados recursivos depende de la cantidad de elementos mayores al numero k que haya.
//siendo ese valor M, la complejidad de _calcular_combinaciones seria O(Mlogn)
//como M es como mucho igual a la cantidad de elementos iniciales
//todo el algoritmo seria O(nlogn)