size_t _raiz_entera(size_t inicio, size_t final, size_t n) {

    size_t medio = (inicio + final)/2;

    if ((medio*medio) == n) return medio;
    if ((medio*medio) < n && (medio+1)*(medio+1) > n) return medio;

    if ((medio*medio) > n) return _raiz_entera(inicio, medio-1, n);
    if ((medio*medio) < n) return _raiz_entera(medio+1, final, n);

}

size_t raiz_entera(size_t n) {
    return _raiz_entera(0, n, n);
}