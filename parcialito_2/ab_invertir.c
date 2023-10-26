#include "ab.h"

void ab_invertir(ab_t* ab) {

    if (!ab) return;
    ab_invertir(ab->izq);
    ab_invertir(ab->der);
    ab_t* aux = ab->der;
    ab->der = ab->izq;
    ab->izq = aux;
}