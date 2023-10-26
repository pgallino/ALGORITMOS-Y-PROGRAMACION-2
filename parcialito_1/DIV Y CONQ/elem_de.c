bool _arreglo_ordenado(int arreglo[], size_t desde, size_t hasta, int* elemento) {
    if (desde == hasta) {
        return true;
    }

    size_t medio = (desde + hasta) / 2;
    bool ord_izq = _arreglo_ordenado(arreglo, desde, medio, elemento);
    bool ord_der = _arreglo_ordenado(arreglo, medio + 1, hasta, elemento);
    bool ord_uni = arreglo[medio] <= arreglo[medio + 1];

    if (ord_uni == false) {
        *elemento = arreglo[medio];
    }

    return ord_izq && ord_uni && ord_der;
}

int elemento_desordenado(int arr[], size_t n) {
    int elemento;
    _arreglo_ordenado(arr, 0, n, &elemento);
    return elemento;
}