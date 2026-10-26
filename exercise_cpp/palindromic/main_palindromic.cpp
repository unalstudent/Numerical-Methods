#include "palindromic.h"
#include <print>

int main(int argc, char const *argv[])
{
    int mayor, fa, fb;
    mayor_palindromo(mayor, fa, fb);

    std::println("El mayor palindromo de 3 digitos es: {} = {} * {}", mayor, fa, fb);
    return 0;
}