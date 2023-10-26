/* 1. Escribir una función que reciba dos cadenas de caracteres y retorne true si ambas palabras son anagramas entre sí, o false
en caso contrario. Dos palabras son anagramas si y solo si una palabra se puede formar reordenando las letras de la otra.
Indicar y justificar la complejidad de la función implementada. Ejemplos de uso:
son_anagramas("iman", "mani") => True
son_anagramas("sol", "losa") => False */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>
#include <stdio.h>

bool anagramas(const char* cadena_1, const char* cadena_2) {
    size_t largo_1 = strlen(cadena_1);
    size_t largo_2 = strlen(cadena_2);
    if (largo_1 != largo_2) return false;
    int apariciones[255]; //tamaño de la tabla ASCII
    hash_t* hash = hash_crear(NULL);
    for(int i = 0; i<largo_1;i++) {
        int caracter = (int)cadena_1[i];
        char string[20];
        sprintf(string, "%d", caracter);
        apariciones[caracter] = (hash_pertenece(hash, string)) ? (*(int*) hash_obtener(hash, string)) + 1 : 1;
        hash_guardar(hash, string, &apariciones[caracter]);
    }
    for(int i = 0; i<largo_2;i++) {
        int caracter = (int)cadena_2[i];
        char string[20];
        sprintf(string, "%d", caracter);
        if (!hash_pertenece(hash, string)) {
            hash_destruir(hash);
            return false;
        }
        if (*(int*)hash_obtener(hash, string) == 0) {
            hash_destruir(hash);
            return false;
        }
        apariciones[caracter] = *(int*) hash_obtener(hash, string)) -1; //resto la aparicion
        hash_guardar(hash, string, &apariciones[caracter]);
    }
    hash_destruir(hash);
    return true;

}
//explicacion del algoritmo:
//Mi idea es llenar un hash con las apariciones de cada letra de la primera cadena.
//luego recorro la segunda cadena y voy restando apariciones.
//si el valor de apariciones es 0 y quiero restar es porque hay mas letras x en una que en la otra. devuelvo false.
//si la letra de la segunda cadena no pertenece al hash, devuelvo false porque no esta en la primera.
//si tenian el mismo largo y pude pasar todos los chequeos, es porque son anagramas.
//hice un poco de lio con el arreglo de apariciones y las claves para que no se pise siempre la misma direccion de memoria.
//
//
//orden del algoritmo:
//es o(n) porque simplemente sumo ciclos for que son de orden o(n). Las del Hash son o(1).