#include <print>
#include "sum_square_difference.h"

int main() {
    long long n = 100;
    long long resultado = total_sum(n);
    
    // Asegúrate de pasar la variable 'resultado' para que se imprima
    std::println("La diferencia entre el cuadrado de la suma y la suma de los cuadrados es: {}", resultado);
    
    return 0;
}