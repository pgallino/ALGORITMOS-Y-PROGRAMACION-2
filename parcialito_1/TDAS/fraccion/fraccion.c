#include <stdlib.h>
#include <stdio.h> // sprintf
#include "fraccion.h"

struct fraccion {

    int num;
    int den;
    char* rep;
    
};

fraccion_t* fraccion_crear(int numerador, int denominador) {

    if (denominador == 0) {
        return NULL;
    }

    fraccion_t *fraccion = malloc(sizeof(fraccion_t));

    if (fraccion == NULL) {
        return NULL;
    }

    fraccion -> rep = malloc(10 * sizeof(char));

    if (fraccion -> rep == NULL) {
        free(fraccion);
        return NULL;
    }

    int temporal;
    int a = numerador;
    int b = denominador;

    while (b != 0) {
        temporal = b;
        b = a % b;
        a = temporal;
    }

    int num_simplificado = numerador / a;
    int den_simplificado = denominador / a;

    fraccion-> num = num_simplificado;
    fraccion -> den = den_simplificado;
    
    return fraccion;

}

void fraccion_destruir(fraccion_t* fraccion) {
    
    free(fraccion -> rep);
    free(fraccion);
}

fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2) {

    int nuevo_denominador = (f1 -> den) * (f2 -> den);
    int nuevo_numerador = (f1 -> num) * (f2 -> den) + (f2 -> num) * (f1 -> den);

    fraccion_t* suma = fraccion_crear(nuevo_numerador, nuevo_denominador);

    if (suma != NULL) {


        fraccion_destruir(f1);
        fraccion_destruir(f2);

    }

    return suma;

}

fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2) {
    
    fraccion_t* multi = fraccion_crear((f1 -> num)*(f2 -> num),(f1 -> den)*(f2 -> den));

    if (multi != NULL) {

        fraccion_destruir(f1);
        fraccion_destruir(f2);

    }

    return multi;
}

int fraccion_parte_entera(fraccion_t* fraccion) {
    
    return (fraccion -> num) / (fraccion -> den);
}

char* fraccion_representacion(fraccion_t* fraccion) {

    if (fraccion -> den == 1) {
        sprintf(fraccion -> rep, "%i", fraccion -> num);
    } else {
       sprintf(fraccion -> rep, "%i/%i", fraccion -> num, fraccion -> den);
    }
    return fraccion -> rep;
}