#include "palindromic.h"

//implementation
bool es_palindromo(int n) {
    int original = n, invertido = 0;
    while (n > 0) {
        invertido = invertido * 10 + n % 10;
        n /= 10;
    }
    return original == invertido;
}

void mayor_palindromo(int &mayor, int &fa, int &fb) {
    mayor = 0;
    fa = 0;
    fb = 0;

    for (int a = 999; a >= 100; a -= 1) {
        // Si a es múltiplo de 11, b puede ser cualquiera.
        // Si no lo es pues b debe ser múltiplo de 11 (el mayor ≤ 999 es 990).
        int b, paso;
        if (a % 11 == 0) {
            b = 999;
            paso = 1;
        }
        else {
            b = 990;
            paso = 11;
        }

        for (; b >= 100; b -= paso) {
            int p = a * b;
            if (p <= mayor) break;     // los siguientes productos serán menores
            if (es_palindromo(p)) {
                mayor = p;
                fa = a;
                fb = b;
            }
        }
    }
}