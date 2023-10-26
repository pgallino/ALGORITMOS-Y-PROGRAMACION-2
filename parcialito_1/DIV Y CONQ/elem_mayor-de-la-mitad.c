int _mas_de_mitad(int* arr, size_t n, size_t inicio, size_t fin, int* diccionario) {
    
    if (inicio == fin) {

        diccionario[arr[inicio]] = diccionario[arr[inicio]] + 1;

        if (diccionario[arr[inicio]] > (int)n/2) {

            return 1;

        } else {

            return 0;
        }
    }

    size_t medio = (inicio + fin) / 2;

    int izq = _mas_de_mitad(arr, n, inicio, medio, diccionario);
    int der = _mas_de_mitad(arr, n, medio + 1, fin, diccionario);

    return izq + der;
}


bool mas_de_mitad(int* arr, size_t n) {

    int* diccionario = malloc(sizeof(int) * n);

    bool valor = _mas_de_mitad(arr, n, 0, n-1, diccionario) > 0 ? true : false;

    free(diccionario);

    return valor;


}