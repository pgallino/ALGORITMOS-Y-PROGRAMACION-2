#include <stdio.h>

void swap(int* x, int* y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void alternar(int* arreglo, int n) {
    
    for (int i = 1; i < n; i = i+2) {

        swap(&arreglo[i], &arreglo[(2 * n - 1) - i]);
    }

}

void imprimir_arreglo(int numeros[], int n) { 
  for (int i = 0; i < n; i++) {
    printf("%d, ", numeros[i]);
  }
}

int main() {

    int arreglo[] = {1,1,1,1,1,2,2,2,2,2};
    imprimir_arreglo(arreglo, 10);
    alternar(arreglo, 5);
    printf("\n");
    imprimir_arreglo(arreglo, 10);
    return 0;
}