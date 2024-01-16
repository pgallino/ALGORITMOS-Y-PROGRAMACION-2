#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está conformada por punteros genéricos */

struct lista;
typedef struct lista lista_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Inserta un elemento al principio de la lista, devuelve NULL en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un elemento al principio de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Inserta un elemento al final de la lista, devuelve NULL en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un elemento al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Elimina el primer elemento de la lista.
// Pre: la lista fue creada.
// Post: se devuelve el elemento eliminado, o NULL si la lista está vacía.
void *lista_borrar_primero(lista_t *lista);

// Devuelve el primer elemento de la lista.
// Pre: la lista fue creada.
// Post: se devuelve el primer elemento, o NULL si la lista está vacía.
void *lista_ver_primero(const lista_t *lista);

// Devuelve el último elemento de la lista.
// Pre: la lista fue creada.
// Post: se devuelve el último elemento, o NULL si la lista está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve la cantidad de elementos en la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Itera los elementos de la lista y aplica a cada uno la función visitar 
// que se recibe por parámetro. El parámetro extra sirve para realizar
// operaciones a lo largo de la iteración, es NULL si no se lo quiere utilizar.
// Pre: la lista fue creada.
// Post: se aplicó la función visitar a todos los elementos de la lista.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/* El iterador recorre los elementos de la lista */
struct lista_iter;
typedef struct lista_iter lista_iter_t;

// Crea un iterador para la lista pasada por parámetro.
// Post: devuelve un nuevo iterador.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza una posición en la lista, si ya no se puede avanzar devuelve false.
// Pre: el iterador fue creado.
// Post: el iterador avanza una posición.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el elemento actual en el que se encuentra el iterador,
// o NULL si la lista está vacía o ya se la recorrió hasta el final.
// Pre: el iterador fue creado.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve true si el iterador recorrió toda la lista,
// o si la lista está vacía, false en otro caso.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento en la lista, en la posición del elemento actual.
// Pre: el iterador fue creado.
// Post: se devolvió true si el elemento fue insertado, false si ocurrió un error.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra el elemento actual de la lista, si está vacía o el iterador se encuentra al final
// devuelve NULL, sino se devuelve el elemento eliminado.
// Pre: el iterador fue creado.
// Post: si la lista no estaba vacía, se devuelve el elemento
// eliminado y la lista tiene un elemento menos.
void *lista_iter_borrar(lista_iter_t *iter);

void pruebas_lista_estudiante(void);

#endif