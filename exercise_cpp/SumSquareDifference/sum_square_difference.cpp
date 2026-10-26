#include "sum_square_difference.h"

// Calcula la suma de los cuadrados
long long sum_square(long long n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

// Calcula el cuadrado de la suma
long long square_sum(long long n) {
    long long suma = n * (n + 1) / 2;
    return suma * suma; 
}

// Retorna la diferencia
long long total_sum(long long n) {
    return square_sum(n) - sum_square(n);
}