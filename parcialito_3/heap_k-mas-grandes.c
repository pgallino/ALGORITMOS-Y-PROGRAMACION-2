"""(★) Implementar una primitiva para el heap (de máximos) que obtenga los 3 elementos más grandes del heap

(★★) Si en el ejercicio anterior vez de quererse los 3 elementos más grandes 
se quisieran los K elementos más grandes ¿cómo se debería proceder? 
¿Cuál terminaría siendo la complejidad del algoritmo?"""

void** devolver_k_mas_grandes(heap_t* heap, size_t k) {
    void** arreglo = malloc(sizeof(void*) * k);
    for(size_t i = 0; i<k; i++) {
        arreglo[i] = heap_desencolar(heap);
    }
    return arreglo
}

//crear arreglo o(N)
//desencolar o(logN)
//desencolar k elementos o(klogN)

