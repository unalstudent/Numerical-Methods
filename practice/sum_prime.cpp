#include <print>

// declaración
bool is_prime(long long n);
long long sum_primes_below(long long limit);

int main(int argc, char const *argv[])
{
    const long long limite = 2'000'000;
    long long resultado = sum_primes_below(limite);

    std::println("la suma de los numeros primos por debajo de {} es {}", limite, resultado);

    return 0;
}

// implementación
bool is_prime(long long n)
{
    if (n < 2) return false;

    for (long long d = 2; d * d <= n; d++)
    {
        if (n % d == 0) return false;   // encontré un divisor: no es primo
    }
    return true;
}

long long sum_primes_below(long long limit)
{
    long long total = 0;

    for (long long n = 2; n < limit; n++)
    {
        if (is_prime(n)) total += n;
    }
    return total;
}