#include <print>

// Declaraciones
long long factorial(long long n);
long long curius(long long n);

int main(int argc, char* const argv[])
{
    long long n = 1000000;

    std::println("Resultado: {}", curius(n));

    return 0;
}

long long factorial(long long n)
{
    long long resultado = 1;

    for (long long i = 2; i <= n; ++i)
    {
        resultado *= i;
    }

    return resultado;
}

long long curius(long long n)
{
    long long sum = 0;

    for (long long i = 1; i < n; ++i)
    {
        long long numero = i;
        long long sumaFactoriales = 0;

        while (numero > 0)
        {
            long long digito = numero % 10;
            sumaFactoriales += factorial(digito);
            numero /= 10;
        }

        if (sumaFactoriales == i)
        {
            sum += i;
        }
    }

    return sum;
}