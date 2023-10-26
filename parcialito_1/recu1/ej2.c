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

//obtengo la primera posición del 1 y al largo del arreglo se la resto.

//Primero divido el problema en 2.
//Luego me quedo con una sola mitad efectuando un solo llamado recursivo.  
//Como además las demás operaciones son O(1), puedo llegar a la siguiente ecuacion de recursión:

//T(n) = 1*T(n/2) + o(1)

//Para aplicar el Teorema del Maestro identifico a, b y c:
// a = 1 ; b = 2 ; c = 0;
// Mediante el Teorema del Maestro obtengo que Logb(a) = 0. Siendo igual al valor de c.
// finalmente aplico n**c logn
//como c es cero me queda O(logn) --> rta
