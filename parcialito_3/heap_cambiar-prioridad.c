//Implementar en C una primitiva para el heap (siendo este un max-heap) que reciba un heap 
//y una función de comparación y lo reordene de manera tal que se se comporte como max-heap 
//para la nueva función de comparación (se cambia la función de prioridad). 
//El orden de dicha primitiva debe ser O(n).

#include "heap.h"

void heap_cambiar_prioridad(heap_t* heap, cmp_func_t nueva_cmp) {
    heap->cmp = nueva_cmp;
    heapify(heap->datos, heap->cant, heap->cmp);
}