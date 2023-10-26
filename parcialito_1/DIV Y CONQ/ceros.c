"""Se tiene un arreglo tal que [1, 1, 1, …, 0, 0, …] (es decir, unos seguidos de ceros). 
Se pide una función de orden O(log(n)) que encuentre el índice del primer 0.
 Si no hay ningún 0 (solo hay unos), debe devolver -1."""

int _primer_cero(int arr[], size_t inicio, size_t final) {

    if (inicio >= final) return -1;

    size_t medio = (inicio + final) /2

    if (arr[medio] == 0 && arr[medio-1] == 1) return medio

    if (arr[medio] == 0) return _primer_cero(arr,inicio,medio-1);
    if (arr[medio] == 1) return _primer_cero(arr,medio+1,final);
}

int primer_cero(int arr[], size_t n) {
    return _primer_cero(arr, 0, n);
}

int _primer_cero(int arr[], size_t inicio, size_t fin) {
    if(inicio == fin)
        return arr[inicio] == 0 ? (int)inicio : -1;

    size_t medio = (inicio + fin) / 2;

    return arr[medio] == 0 ? _primer_cero(arr, inicio, medio-1) : _primer_cero(arr, medio + 1, fin);
    
}


int primer_cero(int arr[], size_t n) {
    return _primer_cero(arr, 0, n - 1);
}