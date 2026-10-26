
// Función para calcular el Máximo Común Divisor (MCD)
long long calcular_mcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Función para calcular el Mínimo Común Múltiplo (MCM) de dos números
long long calcular_mcm(long long a, long long b) {
    if (a == 0 or b == 0) return 0;
    return (a * b) / calcular_mcd(a, b);
}

// Función para hallar el MCM de un rango desde 1 hasta maximo
long long mcm_rango(int maximo) {
    long long resultado;
    long long min = 1;
    for (int i = 1; i <= maximo; ++i) {
        resultado = calcular_mcm(min, i);
    }
    return resultado;
}
