"""Implementar, por división y conquista, una función que determine el mínimo de un arreglo.
 Indicar y justificar el orden."""

int _buscar_minimo(int arr[], size_t inicio, size_t fin) {

    if (inicio == fin) {

        return arr[inicio];
    }

    size_t medio = (inicio + fin) / 2;

    int min_izq = _buscar_minimo(arr, inicio, medio);
    int min_der = _buscar_minimo(arr, medio + 1, fin);
    return (min_izq < min_der) ? min_izq : min_der;
}

int buscar_minimo(int arr[], size_t n) {
    
    return _buscar_minimo(arr, 0, n-1);
}