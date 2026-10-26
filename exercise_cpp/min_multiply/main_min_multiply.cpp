#include "min_multiply.h"
#include <print>
int main() {
    int maximo = 20;
    long long resultado = mcm_rango(maximo);
    std::println("El minimo comun multiplo del 1 al {} es: {}", maximo, resultado);
    return 0;
}