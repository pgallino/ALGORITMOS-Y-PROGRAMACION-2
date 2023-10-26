#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {

    int valor1 = *y;

    *y = *x;
    *x = valor1;
}


int maximo(int vector[], int n) {

    if (n == 0) {

        return -1;

    }

    int pos_max = 0;

    for (int i = 1; i < n; i++) {

        if (vector[i] > vector[pos_max]) {
            
            pos_max = i;
        }

    }

    return pos_max;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {

    int largo = n1 > n2 ? n2 : n1;

    for (int i = 0; i < largo; i++) {

        if (vector1[i] > vector2[i]) {
            return 1;

        } else if (vector1[i] < vector2[i]) {
            return -1;
        }
    }

    if (n1 > n2) {return 1;}
    else if (n2 > n1) {return -1;}
    else {return 0;}
}

void seleccion(int vector[], int n) {

    int pos_max;

    if (n > 1) {

        for (int i = n; i > -1; i--) {

            pos_max = maximo(vector, i);

            swap(&vector[pos_max], &vector[i-1]);
        }
    }
}

