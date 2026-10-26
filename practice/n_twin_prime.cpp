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

    for (long long p = 3; ; p += 2) {
        if (es_primo(p) && es_primo(p + 2)) {
            ++contador;
            if (contador == OBJETIVO) {
                std::println("El par gemelo #{} es ({}, {})", OBJETIVO, p, p + 2);
                break;
            }
        }
    }
    return 0;
}