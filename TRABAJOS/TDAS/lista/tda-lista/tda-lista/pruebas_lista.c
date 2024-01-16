#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_lista_vacia(void) {
    printf("\nINICIO DE PRUEBAS EN LISTA VACIA\n");
    lista_t *lista = lista_crear();
    print_test("crear lista", lista != NULL);
    print_test("la lista está vacía", lista_esta_vacia(lista) == true);
    print_test("desenlistar da NULL", lista_borrar_primero(lista) == NULL);
    print_test("ver_primero da NULL", lista_ver_primero(lista) == NULL);

    lista_destruir(lista, NULL);
}

static void prueba_lista_1_elemento(void) {
    printf("\nINICIO DE PRUEBAS CON UN ELEMENTO\n");
    lista_t *lista = lista_crear();
    int numero = 5;
    print_test("agregar 1", lista_insertar_primero(lista, &numero));
    print_test("la cola tiene elementos", !lista_esta_vacia(lista));
    print_test("ver_primero da el puntero", lista_ver_primero(lista) == &numero);
    print_test("ver_ultimo da el puntero", lista_ver_ultimo(lista) == &numero);
    print_test("eliminar 1", lista_borrar_primero(lista) == &numero);
    print_test("la lista está vacía", lista_esta_vacia(lista));
    print_test("eliminar da NULL", lista_borrar_primero(lista) == NULL);
    print_test("agregar 1 al final", lista_insertar_ultimo(lista, &numero));
    print_test("la cola tiene elementos", !lista_esta_vacia(lista));
    print_test("ver_primero da el puntero", lista_ver_primero(lista) == &numero);
    print_test("ver_ultimo da el puntero", lista_ver_ultimo(lista) == &numero);
    print_test("eliminar 1", lista_borrar_primero(lista) == &numero);
    print_test("la lista está vacía", lista_esta_vacia(lista));
    print_test("eliminar da NULL", lista_borrar_primero(lista) == NULL);

    printf("\nINICIO PRUEBA AGREGAR Y ELIMINAR VARIAS VECES EL MISMO numero\n");
    
    print_test("agregar 1", lista_insertar_ultimo(lista, &numero));
    print_test("ver_primero da el puntero", lista_ver_primero(lista) == &numero);
    print_test("agregar 2", lista_insertar_ultimo(lista, &numero));
    print_test("ver_segundo da el puntero", lista_ver_primero(lista) == &numero);
    print_test("agregar 3", lista_insertar_ultimo(lista, &numero));
    print_test("ver_tercero da el puntero", lista_ver_primero(lista) == &numero);
    print_test("eliminar 1", lista_borrar_primero(lista) == &numero);                
    print_test("eliminar 2", lista_borrar_primero(lista) == &numero);
    print_test("eliminar 3", lista_borrar_primero(lista) == &numero);
    print_test("ver_primero da NULL", lista_ver_primero(lista) == NULL);
    print_test("eliminar da NULL", lista_borrar_primero(lista) == NULL);

    lista_destruir(lista, NULL); //se destruye la lista vacia habiendo eliminado su elemento
}

static void prueba_volumen() {
    printf("\nINICIO PRUEBA VOLUMEN 1000 ELEMENTOS INSERTANDO AL FINAL\n");
    lista_t* lista = lista_crear();
    for (int i = 0; i < 1000; i++) {
        int* puntero = malloc(sizeof(int));
        *puntero = i;
        lista_insertar_ultimo(lista, puntero);
    }

    int flag_eliminado = 1, flag_primero = 1;
    for(int i = 0; i < 1000; i++) {
        int* primero = lista_ver_primero(lista);
        if (i != *primero) flag_primero = 0;
        int* eliminado = lista_borrar_primero(lista);
        if (i != *eliminado) flag_eliminado = 0;
        free(eliminado);
    }
    print_test("los valores eliminados coinciden con los agregados", flag_eliminado);
    print_test("el primer elemento de la cola es el correcto", flag_primero);
    print_test("la lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);

    printf("\nINICIO PRUEBA VOLUMEN 1000 ELEMENTOS INSERTANDO AL PRINCIPIO\n");
    lista = lista_crear();
    for (int i = 0; i < 1000; i++) {
        int* puntero = malloc(sizeof(int));
        *puntero = i;
        lista_insertar_primero(lista, puntero);
    }

    flag_eliminado = 1; flag_primero = 1;
    for(int i = 999; i > -1; i--) {
        int* primero = lista_ver_primero(lista);
        if (i != *primero) flag_primero = 0;
        int* eliminado = lista_borrar_primero(lista);
        if (i != *eliminado) flag_eliminado = 0;
        free(eliminado);
    }
    print_test("los valores eliminados coinciden con los agregados", flag_eliminado);
    print_test("el primer elemento de la cola es el correcto", flag_primero);
    print_test("la lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
}

static void pruebas_null(void) {
    printf("\nINICIO DE PRUEBAS CASOS BORDE NULL\n");

    lista_t* lista = lista_crear();

    print_test("insertar null", lista_insertar_primero(lista, NULL));
    print_test("se inserto null", !lista_esta_vacia(lista));
    print_test("ver_tope null", lista_ver_primero(lista) == NULL);
    print_test("desenlistar null", lista_borrar_primero(lista) == NULL);
    print_test("esta_vacia", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
}

bool sumar(void* dato, void* extra) {
    *(int*) extra += *(int*) dato;
    return true;
}

bool sumar_corte(void* dato, void* extra) {
    if (*(int*) extra + *(int*) dato > 50) return false;
    *(int*) extra += *(int*) dato;
    return true;
}

bool impares(void* dato, void* extra) {
    if (*(int*) dato % 2 != 0) {
        lista_insertar_ultimo((lista_t*) extra, dato);
    }
    return true;
}

static void prueba_iterador_interno(void) {
    printf("\nINICIO DE PRUEBAS SOBRE ITERADOR INTERNO\n");
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    lista_t* lista = lista_crear();
    int suma = 0;
    for (int i=0; i < 10; i++) {
        lista_insertar_ultimo(lista, &data[i]);
    }
    lista_iterar(lista, sumar, &suma);
    print_test("extra es igual a la suma de todos los elementos de la lista", suma == 55);

    int suma_corte = 0;
    lista_iterar(lista, sumar_corte, &suma_corte);
    print_test("el elemento extra no supera la condición de corte", suma_corte < 50);

    lista_t* lista_impares = lista_crear();
    lista_iterar(lista, impares, lista_impares);
    int centinela = 1;
    while(!lista_esta_vacia(lista_impares)) {
        void* eliminado = lista_borrar_primero(lista_impares);
        if (*(int*) eliminado % 2 == 0) {
            centinela = 0;
        }
    }
    print_test("la lista de impares se creo correctamente", centinela);
    lista_destruir(lista, NULL);
    lista_destruir(lista_impares, NULL);
}

static void pruebas_iterador_externo(void) {
    printf("\nINICIO DE PRUEBAS SOBRE ITERADOR EXTERNO\n");
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    lista_t* lista = lista_crear();
    for (int i=0; i < 10; i++) {
        lista_insertar_ultimo(lista, &data[i]);
    }
    lista_iter_t* iterador = lista_iter_crear(lista);
    int elemento1 = 0;
    int elemento2 = 11;
    int elemento3 = 100;
    lista_iter_insertar(iterador, &elemento1);
    print_test("se inserto el elemento 0 al principio de la lista", *(int*) lista_ver_primero(lista) == 0);

    while (!lista_iter_al_final(iterador)) {
        lista_iter_avanzar(iterador);
    }
    lista_iter_insertar(iterador, &elemento2);
    print_test("se inserto el elemento 11 al final de la lista", *(int*) lista_ver_ultimo(lista) == 11);
    lista_iter_destruir(iterador);

    iterador = lista_iter_crear(lista);
    for (int i=0; i < 5; i++) {
        lista_iter_avanzar(iterador);
    }
    lista_iter_insertar(iterador, &elemento3);
    lista_iter_destruir(iterador);
    iterador = lista_iter_crear(lista);
    for (int i=0; i < 5; i++) {
        lista_iter_avanzar(iterador);
    }
    print_test("se inserto el elemento 100 en la posición 5 de la lista", *(int*) lista_iter_ver_actual(iterador) == 100);
    lista_iter_destruir(iterador);

    iterador = lista_iter_crear(lista);
    lista_iter_borrar(iterador);
    print_test("el nuevo primer elemento de la lista es el 1", *(int*) lista_ver_primero(lista) == 1);
    lista_iter_destruir(iterador);

    iterador = lista_iter_crear(lista);
    for (int i=0; i < 11; i++) {
        lista_iter_avanzar(iterador);
    }
    lista_iter_borrar(iterador);
    print_test("el nuevo ultimo elemento de la lista es el 10", *(int*) lista_ver_ultimo(lista) == 10);
    lista_iter_destruir(iterador);

    iterador = lista_iter_crear(lista);
    for (int i=0; i < 5; i++) {
        lista_iter_avanzar(iterador);
    }
    void* eliminado = lista_iter_borrar(iterador);
    print_test("se elimino el elemento 5 de la lista", *(int*) eliminado == 5);
    lista_iter_destruir(iterador);

    iterador = lista_iter_crear(lista);
    for (int i=0; i < 5; i++) {
        lista_iter_avanzar(iterador);
    }
    print_test("el nuevo elemento en la posicion 5 de la lista es el 6", *(int*) lista_iter_ver_actual(iterador) == 6);
    lista_iter_destruir(iterador);
    
    lista_destruir(lista, NULL);
}

void pruebas_lista_estudiante(void) {
    prueba_lista_vacia();
    prueba_lista_1_elemento();
    prueba_volumen();
    pruebas_null();
    prueba_iterador_interno();
    pruebas_iterador_externo();
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif