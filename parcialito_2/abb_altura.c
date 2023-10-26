#include "ab.h"

size_t ab_altura(const ab_t* ab) {

    if (ab == NULL) return 0;
    
    size_t izq = ab_altura(ab->izq);
    size_t der = ab_altura(ab->der);
    return (izq>der) ? izq+1 : der+1;
}