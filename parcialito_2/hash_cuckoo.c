#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hash_struct.h"


/* crea una copia (memoria dinamica) de la cadena pasada por parametro */
char* strdup(const char* org) {
    char* cpy = malloc(sizeof(char) * (strlen(org) + 1));
    if (!cpy) return NULL;
    strcpy(cpy, org);
    return cpy;
}

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hash_struct.h"


/* crea una copia (memoria dinamica) de la cadena pasada por parametro */
char* strdup(const char* org) {
    char* cpy = malloc(sizeof(char) * (strlen(org) + 1));
    if (!cpy) return NULL;
    strcpy(cpy, org);
    return cpy;
}

bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
    // TODO
    // Asumir que no hay que lidiar con potenciales redimensiones (en caso de tener que,
    // devolver false)
    size_t tam = hash->tam_tabla; //tamaño del hash
    const char* clave_2 = clave;
    void* dato_2 = dato;
    size_t pos_2 = h1(clave, tam);
    int num_2 = 1;
    int num_aux;
    const char* clave_aux;
    void* dato_aux;
    int contador = 1;
    if (hash_pertenece(hash, clave)) return false;

    do {
        if (hash->tabla[pos_2].num_fhash == 0) { //si no hay nada inserto y doy true
            hash->tabla[pos_2].num_fhash = num_2;
            hash->tabla[pos_2].clave = strdup(clave_2);
            hash->tabla[pos_2].dato = dato_2;
            hash->cantidad++;
            return true;
        }
        num_aux = hash->tabla[pos_2].num_fhash; //copio todo lo que habia
        clave_aux = hash->tabla[pos_2].clave;
        dato_aux = hash->tabla[pos_2].dato;

        hash->tabla[pos_2].num_fhash = (pos_2 == h1(clave_2,tam)) ? 1 : 2; //inserto en la pos
        hash->tabla[pos_2].clave = strdup(clave_2);
        hash->tabla[pos_2].dato = dato_2;

        pos_2 = (num_aux != 1) ? h1(clave_aux,tam): h2(clave_aux,tam); //cambio los parametros
        clave_2 = clave_aux;
        dato_2 = dato_aux;
        num_2 = (num_aux != 1) ? 1 : 2;
        contador += 1;

    } while(contador != 30);
    return false;
}

bool _hash_guardar2(hash_t* hash, char* copia, void* dato, int fn, size_t tam, int contador) {
    size_t pos = (fn == 1) ? h1((const char*)copia, tam) : h2((const char*)copia, tam);

    if (contador == 30) {
        free(copia);
        return false;
    }

    if (hash->tabla[pos].clave == NULL) {

        hash->tabla[pos].clave = copia;
        hash->tabla[pos].dato = dato;
        hash->tabla[pos].num_fhash = fn;
        hash->cantidad++;
        return true;
    }
    
    char* copia_celda = hash->tabla[pos].clave;
    void* dato_celda = hash->tabla[pos].dato;
    int fn_celda = hash->tabla[pos].num_fhash;

    fn_celda = (fn_celda == 1) ? 2 : 1;

    hash->tabla[pos].clave = copia;
    hash->tabla[pos].dato = dato;
    hash->tabla[pos].num_fhash = fn;

    contador += 1;

    return _hash_guardar(hash, copia_celda, dato_celda, fn_celda, tam, contador);
}

bool hash_guardar2(hash_t* hash, const char* clave, void* dato) {
    if (hash_pertenece(hash, clave)) return false;
    size_t tam = hash->tam_tabla;
    char* copia = strdup(clave);
    size_t pos_i = h1(copia, tam);
    int contador = 1;
    return _hash_guardar(hash,copia,dato,1,tam, contador);
}