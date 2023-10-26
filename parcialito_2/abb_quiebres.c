#include "ab.h"
#include <stdbool.h>

size_t _ab_quiebres(const ab_t* ab, ab_t* anterior) {
    if(!ab) return 0;

    size_t izq = _ab_quiebres(ab->izq, ab);
    size_t der = _ab_quiebres(ab->der, ab);
    bool quiebre_izq = ab->izq == NULL && ab->der != NULL && anterior->izq == ab;
    bool quiebre_der = ab->der == NULL && ab->izq != NULL && anterior->der == ab;
    return izq + der + (quiebre_izq? 1:0) + (quiebre_der? 1:0);

}
size_t ab_quiebres(const ab_t* ab) {
    return _ab_quiebres(ab,ab);
}


size_t ab_quiebres2(const ab_t* ab) {
    if(!ab) return 0;
    size_t n = 0;
    ab_t* h_der = ab->der;
    ab_t* h_izq = ab->izq;

    if(h_der && (!h_der->der && h_der->izq != NULL)) {
        n++;
    }
    if(h_izq && (!h_izq->izq && h_izq->der != NULL)) {
        n++;
    }
    return ab_quiebres2(h_der) + ab_quiebres2(h_izq) + n;
}