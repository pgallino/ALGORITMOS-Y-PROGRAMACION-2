/* Asumiendo que se tiene disponible una implementación completa del TDA Hash,
se desea implementar una función que decida si dos Hash dados representan o no el mismo Diccionario. 
Considere para la solución que es de interés la mejor eficiencia temporal posible. 
Indique, para su solución, eficiencia en tiempo y espacio. 
Nota: Dos tablas de hash representan el mismo diccionario si tienen la misma cantidad de elementos; 
todas las claves del primero están en el segundo; todas las del segundo, en el primero;
y los datos asociados a cada una de esas claves son iguales (se pueden comparar los valores con “==”). */

#include "main.h" // No borrar

bool son_iguales(hash_t* a, hash_t* b) {
    size_t cant_a = hash_cantidad(a);
    size_t cant_b = hash_cantidad(b);
    int centinela = 1;

    if (cant_a != cant_b) return false;
    hash_iter_t* iter = hash_iter_crear(a);
    while (!hash_iter_al_final(iter)) {
        const char* actual = hash_iter_ver_actual(iter);
        if (!hash_pertenece(b, actual)) centinela = 0;
        if (hash_obtener(a, actual) != hash_obtener(b, actual)) centinela = 0;
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    return centinela;
}