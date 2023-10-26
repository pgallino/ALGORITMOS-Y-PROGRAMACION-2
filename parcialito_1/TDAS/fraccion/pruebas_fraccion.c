#include "fraccion.h"
#include <stdio.h>

void pruebas_fraccion_estudiante(void) {

    printf("INICIO DE PRUEBAS\n");
    fraccion_t *fraccion = fraccion_crear(32,0);

    if (fraccion != NULL) {
        printf("%s\n",fraccion_representacion(fraccion));
    } else {
        printf("div por cero\n");
        return;
    }
    fraccion_t *fraccion2 = fraccion_crear(5,8);
    printf("%s\n",fraccion_representacion(fraccion2));
    printf("MULTI\n");
    fraccion_t *fraccion3 = fraccion_mul(fraccion, fraccion2);
    printf("%s\n",fraccion_representacion(fraccion3));
    fraccion_t *fraccion4 = fraccion_crear(2,-5);
    printf("%s\n",fraccion_representacion(fraccion4));
    printf("SUMA\n");
    fraccion_t *fraccion5 = fraccion_sumar(fraccion3, fraccion4);
    printf("%s\n",fraccion_representacion(fraccion5));
    printf("PARTE ENTERA\n");
    printf("%d\n", fraccion_parte_entera(fraccion5));

    fraccion_destruir(fraccion5);


}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_fraccion_estudiante();
    return 0;  // Indica si falló alguna prueba.
}

#endif