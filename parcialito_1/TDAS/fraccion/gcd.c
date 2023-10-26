int maximo_comun_divisor(int a, int b) {
    int temporal;//Para no perder b
    while (b != 0) {
        temporal = b;
        b = a % b;
        a = temporal;
    }
    return a;
}