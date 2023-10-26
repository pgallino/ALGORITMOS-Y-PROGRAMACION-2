/* Implementar una función de orden O(n) que dado un arreglo de n números enteros
 devuelva true o false según si existe algún elemento que aparezca más de la mitad de las veces. 
 Justificar el orden de la solución. Ejemplos:

[1, 2, 1, 2, 3] -> false
[1, 1, 2, 3] -> false
[1, 2, 3, 1, 1, 1] -> true
[1] -> true */

#include "main.h" // No borrar
#include "hash.h"
#include <string.h>
#include <stdio.h>

bool mas_de_mitad(void* arreglo[], size_t n) {
    size_t apariciones[n];
    hash_t* hash = hash_crear(NULL);
    size_t maximo = 0;
    for(size_t i = 0; i<n;i++) {
        char string[20];
        int numero = *(int*)arreglo[i];
        sprintf(string, "%d", numero);
        apariciones[i] = (hash_pertenece(hash, string)) ? (*(size_t*) hash_obtener(hash, string)) + 1 : 1;
        hash_guardar(hash, string, &apariciones[i]);
        if (apariciones[i] > maximo) maximo = apariciones[i];
    }
    hash_destruir(hash);
    return maximo > n/2;
}