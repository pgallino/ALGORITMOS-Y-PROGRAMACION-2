// Implementar una primitiva para el heap (de máximos) 
// que obtenga los 3 elementos más grandes del heap en O(1).

#include "heap_struct.h"
#include "heap.h"
#include <stdlib.h>

void** heap_max3(const heap_t* heap){
    void** arreglo = calloc(heap->cant,sizeof(void*));
    void* padre = heap->cant > 0? heap->datos[0] : NULL;
    void* hijo_der = heap->cant > 1? heap->datos[1] : NULL;
    void* hijo_izq = heap->cant > 2? heap->datos[2] : NULL;
    if (padre) arreglo[0] = padre; else return arreglo;
    if (hijo_der && hijo_izq){
        if (heap->cmp(hijo_der, hijo_izq) > 0){
        arreglo[1] = hijo_der;
        arreglo[2] = hijo_izq;
    } else{
        arreglo[1] = hijo_izq;
        arreglo[2] = hijo_der;
    }
    return arreglo;
    }
    if (hijo_der) arreglo[1] = hijo_der; else arreglo[1] = hijo_izq;    
    return arreglo;
}