#include "ab.h"
#include <stdbool.h>

size_t ab_2_hijos(const ab_t* ab) {

    if(ab==NULL) return 0;

    size_t izq = ab_2_hijos(ab->izq);
    size_t der = ab_2_hijos(ab->der);
    bool dos_hijos = ab->izq != NULL && ab->der != NULL;
    return izq + der + (dos_hijos? 1:0);

}