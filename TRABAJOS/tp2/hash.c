#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define CAPACIDAD_INICIAL 10 
#define COEF_MAX_LLENO 7 / 10
#define COEF_MAX_EXCESO 10
#define COEF_AUMENTO 2
#define COEF_DISMINUCION 2
#define VACIO 0
#define LLENO 1
#define BORRADO 2

typedef struct campo {
    char* clave;
    void* dato;
    size_t estado;
} campo_t;

struct hash {
    campo_t **arreglo;
    size_t cantidad;
    size_t capacidad;
    hash_destruir_dato_t funcion_destruir;
};

campo_t* campo_crear(char* clave, void* dato){
    campo_t* campo = malloc(sizeof(campo_t));
    if (campo == NULL) return NULL;
    campo->clave = clave;
    campo->dato = dato;
    campo->estado = VACIO;
    return campo;
}

campo_t** _crear_arreglo(size_t tam) {
    campo_t** arreglo = malloc(tam * sizeof(campo_t*));
    if (arreglo == NULL) return NULL;
    for (size_t i=0; i < tam; i++) {
        campo_t* campo = campo_crear(NULL, NULL);
        arreglo[i] = campo;
    }
    return arreglo;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t *hash = malloc(sizeof(hash_t));
    if (hash == NULL) return NULL;
    hash->arreglo = _crear_arreglo(CAPACIDAD_INICIAL);
    if (hash->arreglo == NULL) {
        free(hash);
        return NULL;
    }
    hash->capacidad = CAPACIDAD_INICIAL;
    hash->cantidad = 0;
    hash->funcion_destruir = destruir_dato;
    return hash;
}

size_t funcion_hash(const unsigned char *str) {
    /* https://stackoverflow.com/a/7666577/11585163 */
    size_t n = 5381;
    size_t c;
    while ((c = *str++)) {
        n = ((n << 5) + n) + c;
    }
    return n;
}

size_t _devolver_pos(const hash_t *hash, const char *clave) {
    size_t pos = funcion_hash((const unsigned char*) clave) % hash->capacidad;
    campo_t* campo = hash->arreglo[pos];
    while (campo->estado == BORRADO || (campo->estado == LLENO && strcmp(campo->clave, clave))) {
        pos++;
        pos %= hash->capacidad;
        campo = hash->arreglo[pos];
    }
    return pos;
}

bool _arreglo_redimensionar(hash_t *hash, size_t nuevo_tam) {
    campo_t** nuevo_arreglo = _crear_arreglo(nuevo_tam);
    if (nuevo_arreglo == NULL) return false;
    campo_t** arreglo_ant = hash->arreglo;
    size_t capacidad_ant = hash->capacidad;
    hash->arreglo = nuevo_arreglo;
    hash->capacidad = nuevo_tam;
    hash->cantidad = 0;

    for(size_t i=0; i < capacidad_ant; i++) {
        campo_t* campo = arreglo_ant[i];
        if (campo->estado == LLENO) {
            hash_guardar(hash, campo->clave, campo->dato);
            free(campo->clave);
        }
        free(campo);
    }
    free(arreglo_ant);
    return true;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    if (hash->cantidad > hash->capacidad * COEF_MAX_LLENO) {
        bool res = _arreglo_redimensionar(hash, hash->capacidad * COEF_AUMENTO);
        if (res == false) return res;
    }
    
    campo_t* campo = hash->arreglo[_devolver_pos(hash, clave)];
    if (campo->estado == LLENO){
        if (hash->funcion_destruir) hash->funcion_destruir(campo->dato);
    }
    else {
        campo->estado = LLENO;
        char* copia_clave = strdup(clave);
        campo->clave = copia_clave;
        hash->cantidad++;
    }
    campo->dato = dato;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave) {
    if ((hash->cantidad * COEF_MAX_EXCESO < hash->capacidad) && hash->capacidad != CAPACIDAD_INICIAL) {
        _arreglo_redimensionar(hash, hash->capacidad / COEF_DISMINUCION);
    }

    campo_t* campo = hash->arreglo[_devolver_pos(hash, clave)];
    if (campo->estado == VACIO) return NULL;
    void* dato = campo->dato;
    campo->dato = NULL;
    campo->estado = BORRADO;
    hash->cantidad--;
    free(campo->clave);
    return dato;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
    campo_t* campo = hash->arreglo[_devolver_pos(hash,clave)];
    if (campo->estado == VACIO || strcmp(campo->clave, clave)) return NULL;
    return campo->dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {
    campo_t* campo = hash->arreglo[_devolver_pos(hash,clave)];
    if (campo->estado == VACIO) return false;
    return !strcmp(campo->clave, clave);
}

size_t hash_cantidad(const hash_t *hash) {
    return hash->cantidad;
}

void hash_destruir(hash_t *hash) {
    for (size_t i=0; i < hash->capacidad; i++) {
        campo_t* campo = hash->arreglo[i];
        if (campo->estado == LLENO){
            free(campo->clave);
            if (hash->funcion_destruir) hash->funcion_destruir(campo->dato);
        }
        free(campo);
    }
    free(hash->arreglo);
    free(hash);
}


struct hash_iter{
    const hash_t* hash;
    size_t actual;
};

hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    iter->actual = 0;
    iter->hash = hash;
    while(!hash_iter_al_final(iter) && iter->hash->arreglo[iter->actual]->estado != LLENO) {
        iter->actual++;
    }
    return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return false;
    iter->actual++;
    while (!hash_iter_al_final(iter) && iter->hash->arreglo[iter->actual]->estado != LLENO) {
        iter->actual++;
    }
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return NULL;
    return iter->hash->arreglo[iter->actual]->clave;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
    return iter->actual == iter->hash->capacidad;
}

void hash_iter_destruir(hash_iter_t *iter) {
    free(iter);
}