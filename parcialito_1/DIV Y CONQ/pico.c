size_t posicion_pico(int v[], size_t ini, size_t fin) {
    
    size_t medio = (fin + ini) / 2;

    if (v[medio - 1] < v[medio] && v[medio + 1] < v[medio]) {

        return medio;

    } else if (v[medio - 1] < v[medio] && v[medio + 1] > v[medio]) {

        return posicion_pico(v, medio + 1, fin);

    } else if (v[medio - 1] > v[medio] && v[medio + 1] < v[medio]) {

        return posicion_pico(v, ini, medio);
    }
}