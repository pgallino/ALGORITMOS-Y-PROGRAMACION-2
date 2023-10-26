size_t _raiz_entera(size_t inicio, size_t fin, size_t valor) {

    if (inicio == fin) {

        return inicio;
    }

    size_t medio = (fin + inicio) / 2;

    if (medio * medio == valor) {

        return medio;

    } else if (medio * medio < valor && (medio + 1) * (medio + 1) > valor) {

        return medio;
    }
    
    
    else if (medio * medio > valor) {

        return _raiz_entera(inicio, medio, valor);

    } else if (medio * medio < valor) {

        return _raiz_entera(medio + 1, fin, valor);
    }


    

}

size_t raiz_entera(size_t n) {

    return _raiz_entera(0, n, n);
}