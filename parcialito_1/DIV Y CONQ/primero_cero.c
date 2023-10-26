#include <stdio.h>

int _primer_cero(int arr[], int inicio, int fin) {
    
    if (fin == inicio) {

        return arr[inicio] == 0 ? inicio : -1;
    }
    
    int medio = (inicio + fin) / 2;

    return arr[medio] == 0 ? _primer_cero(arr, inicio, medio) : _primer_cero(arr, medio + 1, fin);
}

int primer_cero(int arr[], size_t n) {

    return _primer_cero(arr, 0, (int)n-1);
}

int main() {

    int arreglo1[] = {1,1,1,1,1,0,0,0,0};
    int arreglo2[] = {1,1,1,1,1,1,1,1,0};
    int arreglo3[] = {0,0,0,0,0,0,0,0,0};
    int arreglo4[] = {1,1,0,0,0,0,0,0,0};
    int arreglo5[] = {1,1,1,1,1,1,1,1,1}; //para este caso falopa no anda
	int tam = 9;

    printf("%d\n", primer_cero(arreglo1, tam));
    printf("%d\n", primer_cero(arreglo2, tam));
    printf("%d\n", primer_cero(arreglo3, tam));
    printf("%d\n", primer_cero(arreglo4, tam));
    printf("%d\n", primer_cero(arreglo5, tam));
    return 0;


}