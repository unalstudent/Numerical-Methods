#include <cmath>
#include <print>

bool es_primo(long long n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0) return false;

    const long long limite = static_cast<long long>(std::sqrt(static_cast<double>(n)));
    for (long long i = 3; i <= limite; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    constexpr int OBJETIVO = 10001;
    int contador = 0;
    long long suma_menores = 0;   // suma de p de cada par (p, p+2)
    long long suma_total   = 0;   // suma de p + (p+2) de cada par

    for (long long p = 3; contador < OBJETIVO; p += 2) {
        if (es_primo(p) && es_primo(p + 2)) {
            ++contador;
            suma_menores += p;
            suma_total   += p + (p + 2);
        }
    }

    std::println("Suma de los primos menores de los primeros {} pares: {}", OBJETIVO, suma_menores);
    std::println("Suma de todos los primos de esos {} pares:           {}", OBJETIVO, suma_total);
    return 0;
}