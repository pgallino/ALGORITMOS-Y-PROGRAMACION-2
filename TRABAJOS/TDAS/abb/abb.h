#include <stdbool.h>
#include <stddef.h>

typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;
// Función para destruir dato
typedef void (*abb_destruir_dato_t) (void *);

/*  Función para comparar dos claves, devuelve 0 si son iguales, un int > 0 si la primer cadena
es mayor que la segunda, o un int < 0 si la primer cadena es menor. */ 
typedef int (*abb_comparar_clave_t) (const char *, const char *);

/* Crea el ABB */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/*  Guarda un elemento en el ABB, si la clave ya se encuentra en la
estructura, la reemplaza. De no poder guardarlo devuelve false. 
Pre: El ABB fue inicializado
Post: Se almacenó el par (clave, dato) */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Borra un elemento del ABB y devuelve el dato asociado.  
Devuelve NULL si la clave no estaba.
Pre: El ABB fue inicializado
Post: El elemento fue borrado de la estructura y se lo devolvió,
en el caso de que estuviera guardado. */
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el valor de un elemento del ABB, si la clave no se encuentra
devuelve NULL.
Pre: El ABB fue inicializado */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si clave pertenece o no al ABB.
Pre: El ABB fue inicializado */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del ABB.
Pre: El ABB fue inicializado */
size_t abb_cantidad(const abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
destruir para cada par (clave, dato).
Pre: El ABB fue inicializado
Post: El ABB fue destruido */
void abb_destruir(abb_t *arbol);

/* Recorre el ABB in-order y aplica la función visitar pasada por parámentro
a todos los elementos.
Pre: el ABB fue inicializado
Post: se aplicó la función visitar a todos los elementos del ABB */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* Iterador del ABB */

// Crea iterador
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Avanza iterador
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Comprueba si terminó la iteración
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye el iterador
void abb_iter_in_destruir(abb_iter_t* iter);