int _primer_uno(int arr[], size_t inicio, size_t final) {

    if (inicio >= final) return -1;

    size_t medio = (inicio + final) /2

    if (arr[medio] == 1 && arr[medio-1] == 0) return medio

    if (arr[medio] == 1) return _primer_uno(arr,inicio,medio-1);
    if (arr[medio] == 0) return _primer_uno(arr,medio+1,final);
}

int contar_unos(int arr[], size_t n) {
    int pos_primer_uno = _primer_uno(arr, 0, n);
    if (pos_primer_uno > 0) return n - pos_primer_uno;
    return 0;
}
