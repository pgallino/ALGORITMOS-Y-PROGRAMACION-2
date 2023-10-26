#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#define VOLUMEN 1000

int comp_ints(const void *a, const void *b) { //funcion de comparacion
    int a_int = *(int*)a;
    int b_int = *(int*)b;
    if (a_int > b_int) return 1;
    if (b_int > a_int) return -1;
    return 0;
}

static void prueba_heap_vacio(void) {

    printf("INICIO DE PRUEBAS EN HEAP VACIO\n");
    heap_t *heap = heap_crear(comp_ints);
    print_test("crear heap", heap != NULL);
    print_test("el heap está vacío", heap_esta_vacio(heap) == true);
    print_test("desencolar da NULL", heap_desencolar(heap) == NULL);
    print_test("ver_max da NULL", heap_ver_max(heap) == NULL);

    heap_destruir(heap, NULL);
}

static void prueba_heap_1_elemento(void) {

    printf("INICIO DE PRUEBAS CON HEAP DE UN PUNTERO\n");
    heap_t *heap1 = heap_crear(comp_ints);
    int numero = 5;
    void* puntero = &numero;
    print_test("encolar 1", heap_encolar(heap1, puntero));
    print_test("el heap tiene elementos", heap_esta_vacio(heap1) == false);
    print_test("ver_maximo da el puntero", heap_ver_max(heap1) == puntero);
    print_test("desencolar 1", heap_desencolar(heap1) == puntero);
    print_test("el heap está vacío", heap_esta_vacio(heap1) == true);
    print_test("desencolar da NULL", heap_desencolar(heap1) == NULL);

    heap_destruir(heap1, NULL);
}

static void prueba_algunos_desordenados(void) {
    printf("INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");
    heap_t *heap2 = heap_crear(comp_ints);
    int arreglo_insercion[] = {4,2,7,10,4,3,8,5};
    int arreglo_desencolado[] = {10,8,7,5,4,4,3,2};
    int centinela = 1;
    for(int i = 0; i<8;i++) {
        heap_encolar(heap2, &arreglo_insercion[i]);
    }
    for(int i = 0; i<8;i++) {
        int valor = *(int*)heap_desencolar(heap2);
        if (valor != arreglo_desencolado[i]) {
            centinela = 0;
        }
    }
    print_test("prueba de algunos elementos exitosa", centinela != 0); //si no coincide en algun momento el desencolado centinela = 0
    heap_destruir(heap2, NULL);
}

static void heap_volumen(void) {

    printf("INICIO PRUEBA DE VOLUMEN\n");  //apilo 1000 punteros y luego los desapilo.

    heap_t *heap3 = heap_crear(comp_ints);

    int *arreglo = malloc(VOLUMEN * sizeof(int*));
    int centinela = 1;

    for(int i = 0; i < VOLUMEN; i++) { //lleno el arreglo con punteros

        arreglo[i] = i;
        heap_encolar(heap3, &arreglo[i]);
    }
    for(int i = VOLUMEN - 1; i > -1; i--) {

        if (heap_desencolar(heap3) != &arreglo[i]) {
            centinela = 0;
        }
    }
    print_test("prueba de volumen", centinela != 0); //si no coincide en algun momento el desencolado centinela = 0

    free(arreglo);
    heap_destruir(heap3, NULL);
}

static void prueba_acciones_NULL(void) {

    printf("INICIO DE PRUEBAS CASOS BORDE NULL\n");

    heap_t *heap4 = heap_crear(comp_ints);

    print_test("encolar null", heap_encolar(heap4, NULL));
    print_test("esta_vacia null", heap_esta_vacio(heap4) == false);
    print_test("ver_tope null", heap_ver_max(heap4) == NULL);
    print_test("desencolar null", heap_desencolar(heap4) == NULL);
    print_test("esta_vacia", heap_esta_vacio(heap4) == true);

    heap_destruir(heap4, NULL);
}

static void prueba_destruir_con_elementos(void) {

    printf("PRUEBA DESTRUIR CON ELEMENTOS\n");

    heap_t *heap5 = heap_crear(comp_ints);
    int* num_1 = malloc(sizeof(int));
    *num_1 = 1;
    int* num_2 = malloc(sizeof(int));
    *num_2 = 2;
    int* num_3 = malloc(sizeof(int));
    *num_3 = 3;

    heap_encolar(heap5,num_1);
    heap_encolar(heap5,num_2);
    heap_encolar(heap5,num_3);

    heap_destruir(heap5, free);

    print_test("Comprobar la destrucción correcta de los elementos", 1);
}

static void prueba_crear_heap_con_arreglo_existente(void) {

    printf("PRUEBA CREAR HEAP CON ARREGLO\n");

    int arreglo_insercion[] = {4,2,7,10,4,3,8,5};
    int arreglo_desencolado[] = {10,8,7,5,4,4,3,2};
    int centinela = 1;
    void** arreglo_existente = malloc(8 * sizeof(void*));
    for(int i = 0; i<8;i++) {
        arreglo_existente[i] = &arreglo_insercion[i];
    }
    heap_t *heap6 = heap_crear_arr(arreglo_existente, 8, comp_ints);
    for(int i = 0; i<8;i++) {
        if (*(int*)heap_desencolar(heap6) != arreglo_desencolado[i]) {
            centinela = 0;
        }
    }
    print_test("prueba crear heap con arreglo exitosa", centinela != 0); //si no coincide en algun momento el desencolado centinela = 0
    free(arreglo_existente);
    heap_destruir(heap6, NULL);
}

static void prueba_heapsort(void) {

    printf("INICIO PRUEBA HEAPSORT\n");
    int arreglo_a_ordenar[] = {4,2,7,10,4,3,8,5};
    int arreglo_ordenado[] = {2,3,4,4,5,7,8,10};
    int centinela = 1;
    void** arreglo = malloc(8 * sizeof(void*));
    for(int i = 0; i<8;i++) {
        arreglo[i] = &arreglo_a_ordenar[i];
    }
    heap_sort(arreglo, 8, comp_ints);
    for(int i = 0; i<8;i++) {
        if (*(int*)arreglo[i] != arreglo_ordenado[i]) {
            centinela = 0;
        }
    }
    print_test("prueba heapsort", centinela != 0); //si no coincide en algun momento el desencolado centinela = 0
    free(arreglo);
}

void pruebas_heap_estudiante() {
    prueba_heap_vacio();
    prueba_heap_1_elemento();
    prueba_algunos_desordenados();
    heap_volumen();
    prueba_acciones_NULL();
    prueba_destruir_con_elementos();
    prueba_crear_heap_con_arreglo_existente();
    prueba_heapsort();

    // ...
}


/* 
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
