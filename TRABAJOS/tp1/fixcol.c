#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define POS_ARG_TAM_COLUMNA 1
#define POS_ARG_NOMBRE_ARCHIVO 2
#define CANT_PARAMETROS_MAXIMO 3
#define CANT_PARAMETROS_MINIMO 2

void fixcol(int tamanio, FILE* entrada) {

    tamanio++; //por los \0 de las cadenas
    char* cadena = malloc(sizeof(char) * tamanio);
    if (cadena) {
        while ((fgets(cadena, tamanio, entrada)) != NULL) {
            if (cadena[0] == '\n') continue;
            (cadena[strlen(cadena)-1] == '\n') ? fprintf(stdout, "%s", cadena) : fprintf(stdout, "%s\n", cadena);
        }
        free(cadena);
    }
    fclose(entrada);
}

int devolver_error_de_parametros() { //tal vez es absurdo (porque son dos lineas), pero para no repetir tanto.
    fprintf(stderr, "%s","Error: Cantidad erronea de parametros");
    return 0;
}

int chequeo_parametros(int argc, char* argv[], FILE* entrada, int* tamanio) {

    if (!entrada) {
        fprintf(stderr, "%s", "Error: archivo fuente inaccesible");
        return 0;
    }

    if (argc > CANT_PARAMETROS_MAXIMO || argc < CANT_PARAMETROS_MINIMO) {
        return devolver_error_de_parametros();
    }

    for (int i = 0; argv[POS_ARG_TAM_COLUMNA][i] != '\0'; i++) {
        if (isalpha(argv[POS_ARG_TAM_COLUMNA][i])) {
            return devolver_error_de_parametros();
        }
    }
    *tamanio = atoi(argv[POS_ARG_TAM_COLUMNA]);
    if (!*tamanio) {
        return devolver_error_de_parametros();
    }
    return 1;
}

int main(int argc, char* argv[]) {

    int* tamanio = malloc(sizeof(int*));
    FILE* entrada = (argc == CANT_PARAMETROS_MAXIMO) ? fopen(argv[POS_ARG_NOMBRE_ARCHIVO], "r") : stdin;
    if (!chequeo_parametros(argc, argv, entrada, tamanio)) {
        fclose(entrada);
        free(tamanio);
        return 0;
    }
    fixcol(*tamanio, entrada);
    free(tamanio);
    return 0;
}