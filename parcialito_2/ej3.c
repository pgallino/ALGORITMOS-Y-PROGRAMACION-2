/* 6. Dado un árbol binario que tiene como datos números enteros, 
implementar una primitiva que reemplace el valor de todos
los nodos del árbol de manera tal que cada nodo X tenga como valor la cantidad de nodos que existen en la sub-rama
de ese nodo X. En otras palabras, para cada nodo el valor resultante representa su cantidad de hijos,
nietos, bis-nietos, bis-bis-nietos, etc. 
Ayuda: para la raíz, este valor es igual a la cantidad de elementos en el árbol, menos 1. Para las hojas,
el valor es de 0, ya que no tiene descendientes. ¿Cuál es el orden de la primitiva implementada? 
¿Qué tipo de recorrido utilizaste? La estructura de cada nodo es la siguiente:
typedef struct ab_t {
int valor;
struct ab_t* izq;
struct ab_t* der
} ab_t; */

#include <stddef.h>

typedef struct ab_t {
int valor;
struct ab_t* izq;
struct ab_t* der;
} ab_t;

int _ab_cantidad(ab_t* ab) {
    if (ab == NULL) return 0;
    
    int izq = _ab_cantidad(ab->izq);
    int der = _ab_cantidad(ab->der);
    int cantidad = izq + der + 1; //obtengo la cantidad de hijos hasta ahi
    ab->valor = cantidad-1;
    return cantidad;
}

void cant_nodos_debajo(ab_t* ab) {
    _ab_cantidad(ab);
}

//estoy utilizando un post order ya que primero llamo para la izq y la der y por último a la raiz para cambiar su valor.
//el orden es o(n) ya que para contar los hijos tengo que visitarlos todos.