#include "ab.h"

int ab_suma(const ab_t* ab) {
    if (ab == NULL) return 0;
    
    size_t izq = ab_suma(ab->izq);
    size_t der = ab_suma(ab->der);
    return izq + der + ab->dato;
}