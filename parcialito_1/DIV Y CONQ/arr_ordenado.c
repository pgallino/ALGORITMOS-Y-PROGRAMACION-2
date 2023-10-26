#include <stdio.h>
#include <stdbool.h>

bool _arreglo_ordenado(int arr[], size_t inicio, size_t fin) {
    
    
    if (fin - inicio == 1 || inicio == fin) {

        return arr[fin] >= arr[inicio] ? true : false;
    }

    size_t mitad = (fin + inicio) / 2;

    bool izq = _arreglo_ordenado(arr, inicio, mitad);
    bool der = _arreglo_ordenado(arr, mitad + 1, fin);
    return der && izq && arr[mitad] <= arr[mitad + 1] ? true : false;
}

bool arreglo_ordenado(int arr[], size_t n) {

    if (n == 0) return true;

    return _arreglo_ordenado(arr, 0, n-1);
}

int main() {

    int arreglo1[] = {0,1,2,3,4,5,6,9,8};
    int arreglo2[] = {2,4,6,8,10,12,13,14,15};
    int arreglo3[] = {-2,6,3,4,5,6,7,8,9};
    int arreglo4[] = {0,1,2,3,4,5,6,7,8};
    int arreglo5[] = {-31,-21,-20,-16,4,5,6,7,8};
	int tam = 9;

    printf("%d\n", arreglo_ordenado(arreglo1, tam));
    printf("%d\n", arreglo_ordenado(arreglo2, tam));
    printf("%d\n", arreglo_ordenado(arreglo3, tam));
    printf("%d\n", arreglo_ordenado(arreglo4, tam));
    printf("%d\n", arreglo_ordenado(arreglo5, tam));
    return 0;


}