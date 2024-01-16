#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#define VOLUMEN 1000

static void prueba_cola_vacia(void) {

    printf("INICIO DE PRUEBAS EN cola VACIA\n");
    cola_t *cola = cola_crear();
    print_test("crear cola", cola != NULL);
    print_test("la cola está vacía", cola_esta_vacia(cola) == true);
    print_test("desencolar da NULL", cola_desencolar(cola) == NULL);
    print_test("ver_primero da NULL", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
}

static void prueba_cola_1_elemento(void) {

    printf("INICIO DE PRUEBAS CON ENCOLADO DE UN ELEMENTO\n");
    cola_t *cola1 = cola_crear();
    int numero = 5;
    print_test("encolar 1", cola_encolar(cola1, &numero));
    print_test("la cola tiene elementos", cola_esta_vacia(cola1) == false);
    print_test("ver_primero da el puntero", cola_ver_primero(cola1) == &numero);
    print_test("desencolar 1", cola_desencolar(cola1) == &numero);
    print_test("la cola está vacía", cola_esta_vacia(cola1) == true);
    print_test("desencolar da NULL", cola_desencolar(cola1) == NULL);

    cola_destruir(cola1, NULL); //se destruye la cola vacía habiendo desencolado en el medio
}

static void prueba_pocos_elementos(void) {

    cola_t *cola2 = cola_crear();

    printf("INICIO DE PRUEBAS CON ENCOLADO DE MULTIPLES PUNTEROS\n");

    int numero1 = 3;
    void* puntero1 = &numero1;

    int numero2 = 8;
    void* puntero2 = &numero2;

    int numero3 = 2;
    void* puntero3 = &numero3;

    print_test("encolar 1", cola_encolar(cola2, puntero1));
    print_test("encolar 2", cola_encolar(cola2, puntero2));
    print_test("encolar 3", cola_encolar(cola2, puntero3));
    print_test("desencolar 1", cola_desencolar(cola2) == puntero1);
    print_test("desencolar 2", cola_desencolar(cola2) == puntero2);
    print_test("desencolar 3", cola_desencolar(cola2) == puntero3);

    cola_destruir(cola2, NULL);

}

static void prueba_volumen(void) {

    printf("INICIO PRUEBA DE VOLUMEN\n");  //apilo 1000 punteros y luego los desapilo.
    cola_t *cola3 = cola_crear();
    
    int *arreglo = malloc(VOLUMEN * sizeof(int*));
    int centinela = 1;

    for(int i = 0; i < VOLUMEN; i++) { //lleno el arreglo con punteros y encolo

        arreglo[i] = i;
        cola_encolar(cola3, &arreglo[i]);
    }
    for(int i = 0; i < 1000; i++) {

        if (cola_desencolar(cola3) != &arreglo[i]) centinela = 0;
    }

    print_test("prueba de volumen", centinela != 0); //si no coincide en algun momento el desapilado centinela = 0

    free(arreglo);
    cola_destruir(cola3, NULL);
}

static void pruebas_null(void) {

    printf("INICIO DE PRUEBAS CASOS BORDE NULL\n");

    cola_t *cola4 = cola_crear();

    print_test("encolar null", cola_encolar(cola4, NULL));
    print_test("se encoló null", cola_esta_vacia(cola4) == false);
    print_test("ver_tope null", cola_ver_primero(cola4) == NULL);
    print_test("desencolar null", cola_desencolar(cola4) == NULL);
    print_test("esta_vacia", cola_esta_vacia(cola4) == true);

    cola_destruir(cola4, NULL);

}

static void destruccion_con_null(void) {
    
    printf("INICIO DE PRUEBAS DE DESTRUCCIÓN CON NULL\n");
    cola_t *cola5 = cola_crear();

    int* numero1 = malloc(sizeof(int));
    *numero1 = 1;

    int* numero2 = malloc(sizeof(int));
    *numero2 = 2;

    int* numero3 = malloc(sizeof(int));
    *numero3 = 3;

    print_test("encolar 1", cola_encolar(cola5, numero1));
    print_test("encolar 2", cola_encolar(cola5, numero2));
    print_test("encolar 3", cola_encolar(cola5, numero3));

    printf("DESTRUCCIÓN SIN DESENCOLAR\n");

    cola_destruir(cola5, NULL); //destruyo la cola con los elementos dentro con NULL

    print_test("los datos no se destruyeron", *numero1 == 1); //puedo usar los datos de los nodos eliminados

    free(numero1);
    free(numero2);
    free(numero3); //libero asi no hay perdida de memoria

}

static void destruccion_con_free(void) {

    printf("INICIO DE PRUEBAS DE DESTRUCCIÓN CON FREE\n");
    
    cola_t *cola6 = cola_crear();

    int* numero1 = malloc(sizeof(int));
    *numero1 = 1;

    int* numero2 = malloc(sizeof(int));
    *numero2 = 2;

    int* numero3 = malloc(sizeof(int));
    *numero3 = 3;

    print_test("encolar 1", cola_encolar(cola6, numero1));
    print_test("encolar 2", cola_encolar(cola6, numero2));
    print_test("encolar 3", cola_encolar(cola6, numero3));

    cola_destruir(cola6, free);

    //si quisiera usar alguno de los punteros desencolados habria invalid read
    //no se produce perdida de memoria
}

void _cola_destruir(void* dato) { //wrapper para destruir colas

    cola_destruir(dato, NULL);
}

static void destruccion_con_funcion(void) {

    printf("INICIO DE PRUEBAS DE DESTRUCCIÓN CON FUNCION\n");

    cola_t *cola7 = cola_crear();
    cola_t *cola8 = cola_crear();
    cola_t *cola9 = cola_crear();

    print_test("encolar una cola", cola_encolar(cola7, cola8));
    print_test("encolar otra cola", cola_encolar(cola7, cola9));

    cola_destruir(cola7, _cola_destruir);

    printf("LA COLA SE DESTRUYÓ, COMPROBAR QUE NO HAYA ERRORES DE MANEJO DE MEMORIA\n");

    //encolo colas dentro de una cola y luego desencolo
}

void pruebas_cola_estudiante() {
    prueba_cola_vacia();
    prueba_cola_1_elemento();
    prueba_pocos_elementos();
    prueba_volumen();
    pruebas_null();
    destruccion_con_null();
    destruccion_con_free();
    destruccion_con_funcion();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif