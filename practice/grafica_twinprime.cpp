#include <print>
#include <cmath>
#include <string>
#include <fstream> // para imprimir y leer archivos

bool is_prime(long mynum);
void twin_primes(long a, long b, std::string filename);

int main(void)
{
    long a = 3;       // limite inferior
    long b = 10000;   // limite superior
    twin_primes(a, b, "gemelos.txt");

    return 0;
}

void twin_primes(long a, long b, std::string filename)
{
    // abrir el archivo
    std::ofstream fout(filename);

    // encabezado (python ignora las lineas que empiezan con #)
    std::println(fout, "# norma p");

    // para todos los numeros desde a hasta b-2 -> ii
    for (long ii = a; ii + 2 <= b; ii++) {
        // si ii y ii+2 son primos, es un par de gemelos
        if (is_prime(ii) and is_prime(ii + 2)) {
            double p = ii;
            double q = ii + 2;
            double norma = std::sqrt(p*p + q*q);
            std::println(fout, "{:.6f} {}", norma, ii);
        }
    }

    // cerrar el archivo
    fout.close();
}

bool is_prime(long mynum)
{
    if (mynum <= 1) return false;

    for (long ii = 2; ii <= std::sqrt(mynum); ii++)
    {
        if (mynum % ii == 0) { // encontre un divisor
            return false;
        }
    }
    return true;
}