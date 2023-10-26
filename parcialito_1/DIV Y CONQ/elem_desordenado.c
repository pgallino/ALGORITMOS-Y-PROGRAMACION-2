#include <stdio.h>

int _elem_desordenado(int arr[], size_t inicio, size_t fin) {

    if (fin == inicio) {

        return 0;
    }

    size_t medio = (inicio + fin) / 2;

    if (medio == 0) {

        return arr[medio] > arr[medio + 1] ? arr[medio] : 0;
    }

    if (arr[medio] > arr[medio - 1] && arr[medio] > arr[medio + 1]) {

        return arr[medio];
    } 

    int izq = _elem_desordenado(arr, inicio, medio);
    int der = _elem_desordenado(arr, medio+1, fin);
    return izq + der;

}

int elem_desordenado(int arr[], size_t n) {

    return _elem_desordenado(arr, 0, n-1);
}

int main() {

    int arreglo1[] = {0,1,2,3,4,5,6,40,8};
    int arreglo2[] = {2,4,6,8,40,12,13,14,15};
    int arreglo3[] = {40,1,3,4,5,6,7,8,9};
    int arreglo4[] = {0,1,2,3,4,5,6,7,8};
    int arreglo5[] = {-31,-21,-20,-16,4,5,6,-30,9}; //para este caso falopa no anda
	int tam = 9;

    printf("%d\n", elem_desordenado(arreglo1, tam));
    printf("%d\n", elem_desordenado(arreglo2, tam));
    printf("%d\n", elem_desordenado(arreglo3, tam));
    printf("%d\n", elem_desordenado(arreglo4, tam));
    printf("%d\n", elem_desordenado(arreglo5, tam));
    return 0;


}