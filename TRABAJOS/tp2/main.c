#include <stdio.h>
#include <stdlib.h>
#include "algogram.h"
#include "funcs.h"
#define NUM_PARAMS 2
#define POS_ARG_NOMBRE_ARCHIVO 1

int main(int argc, char* argv[]) {
    if (argc != NUM_PARAMS) {
        fprintf(stdout, "Error: Cantidad erronea de parametros\n");
        return -1;
    }
    FILE* archivo = fopen(argv[POS_ARG_NOMBRE_ARCHIVO], "r");
    if (archivo == NULL) {
        fprintf(stdout, "Error: archivo fuente inaccesible\n");
        return -1;
    }
    hash_t* usuarios = procesar_usuarios(archivo);
    fclose(archivo);
    if (!usuarios) return -1;
    algogram_t* algogram = algogram_crear(usuarios);
    hash_destruir(usuarios);
    if (!algogram) return -1;
    esperar_cmd(algogram);
    algogram_destruir(algogram);
    return 0;
}