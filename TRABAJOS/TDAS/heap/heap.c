#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#define MIN_LARGO 20
#define COEF_AUMENTO 2
#define COEF_DISMIN 2
#define COEF_MAX_EXCESO 4

struct heap {
    void** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

void _swap(void** arr, size_t pos1, size_t pos2) {
    void* aux = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = aux;
}

size_t _maximo(void** arr, size_t padre, size_t h_izq, size_t h_der, cmp_func_t cmp) {
    size_t max = padre;
    max = (cmp(arr[h_izq], arr[max]) > 0) ? h_izq : max;
    if (h_der) max = (cmp(arr[h_der], arr[max]) > 0) ? h_der : max;
    return max;
}

void _upheap(void** arr, size_t hijo, cmp_func_t cmp) {
    if (!hijo) return;
    size_t padre = (hijo - 1) / 2;
    if (cmp(arr[padre], arr[hijo]) < 0) {
        _swap(arr, padre, hijo);
        _upheap(arr, padre, cmp);
    }
}

void _downheap(void** arr, size_t cant, size_t padre, cmp_func_t cmp) {
    if (padre >= (cant) / 2) return;
    size_t h_izq = 2 * padre + 1;
    size_t h_der = (2 * padre + 2) >= cant ? 0 : 2 * padre + 2;
    size_t max = _maximo(arr, padre, h_izq, h_der, cmp);
    if (max != padre) {
        _swap(arr, padre, max);
        _downheap(arr, cant, max, cmp);
    }
}

bool _heap_redimensionar(heap_t* heap, size_t tam) {
    void* aux = realloc(heap->datos, tam * sizeof(void*));
    if (!aux) return false;
    heap->datos = aux;
    heap->tam = tam;
    return true;
}

void _heapify(void** arr, size_t cant, cmp_func_t cmp) {
    size_t i = cant-1;
    while(i != 0) {
        _downheap(arr, cant, i, cmp);
        i--;
    }
    _downheap(arr, cant, i, cmp);
}

heap_t *heap_crear(cmp_func_t cmp) {
    heap_t* heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;
    heap->cant = 0;
    heap->tam = MIN_LARGO;
    heap->cmp = cmp;
    heap->datos = malloc(MIN_LARGO * sizeof(void*));
    if (!heap->datos) {
        free(heap);
        return NULL;
    }
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t* heap = heap_crear(cmp);
    if (!heap) return NULL;
    for (size_t i=0; i < n; i++) {
        if (heap->cant == heap->tam) _heap_redimensionar(heap, heap->tam * COEF_AUMENTO);
        heap->datos[i] = arreglo[i];
        heap->cant++;
    }
    _heapify(heap->datos, heap->cant, heap->cmp);
    return heap;
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap) {
    return heap->cant == 0;
}

void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    return heap->datos[0];
}

bool heap_encolar(heap_t *heap, void *elem) {
    if ((heap->cant == heap->tam) && !_heap_redimensionar(heap, heap->tam * COEF_AUMENTO)) return false;
    heap->datos[heap->cant] = elem;
    _upheap(heap->datos, heap->cant++, heap->cmp);
    return true;
}

void *heap_desencolar(heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    if (heap->tam > MIN_LARGO && (heap->cant * COEF_MAX_EXCESO < heap->tam)) _heap_redimensionar(heap, heap->tam / COEF_DISMIN);
    void* dato = heap->datos[0];
    heap->datos[0] = NULL;
    _swap(heap->datos, 0, --heap->cant);
    _downheap(heap->datos, heap->cant, 0, heap->cmp);
    return dato;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)) {
    while (!heap_esta_vacio(heap)) {
        void* dato = heap_desencolar(heap);
        if (destruir_elemento) destruir_elemento(dato);
    }
    free(heap->datos);
    free(heap);
}

void _heap_sort(void *elementos[], size_t ultimo, cmp_func_t cmp) {

    if (ultimo == 1) return;
    _swap(elementos, 0, --ultimo);
    _downheap(elementos, ultimo, 0, cmp);
    _heap_sort(elementos, ultimo, cmp);
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    _heapify(elementos, cant, cmp);
    _heap_sort(elementos, cant, cmp);
}