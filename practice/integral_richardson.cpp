// richardson.cpp
// Integral por extrapolación de Richardson aplicada a la regla del trapecio
// (funciones trapezoid y richardson del profesor).
//
// Mismo problema que trapecio.cpp: recuperar
//   V(x) = ∫_0^x f(t) dt,   f(x) = 2 sin(x) + 2 x cos(x),   V exacto = 2 x sin(x)
//
// El paso h = Δx se lee de la línea de comandos. Para cada x = i*h en
// 0 <= x <= 2.5 se integra de 0 a x. Salida en pantalla, tres columnas
// (notación científica, 16 decimales):
//   x    valor exacto    valor numérico (Richardson)
//
// Compilar y ejecutar:
//   g++-14 -std=c++23 -O2 -Wall -Wextra richardson.cpp -o richardson.x && ./richardson.x 0.02

#include <cstdlib>     // std::atof, std::lround
#include <cmath>       // std::sin, std::cos, std::pow
#include <functional>  // std::function
#include <print>       // std::println (C++23)

// fptr:      cualquier objeto invocable con firma double(double)  (el integrando)
// algintptr: cualquier objeto invocable con firma
//            double(a, b, nrect, f)  (un algoritmo de integración, p. ej. trapezoid)
using fptr      = std::function<double(double)>;
using algintptr = std::function<double(double, double, int, fptr)>;

double integrand(double x);
double exact_integral(double x);
double trapezoid(double a, double b, int nrect, fptr f);
double richardson(double a, double b, int nrect, int alpha, algintptr I, fptr f);


int main(int argc, char **argv)
{
  if (argc < 2) {
    std::println(stderr, "Uso: {} h", argv[0]);
    return 1;
  }

  const double h    = std::atof(argv[1]);  // paso h = Δx
  const double xmax = 2.5;
  const int N = static_cast<int>(std::lround(xmax / h));

  // Orden del error del algoritmo base: el trapecio tiene error O(h^2),
  // así que alpha = 2.
  const int alpha = 2;

  for (int i = 0; i <= N; ++i) {
    const double x = i * h;  // límite superior de la integral

    // Valor exacto: 2 x sin x
    const double I_exact = exact_integral(x);

    // Valor numérico: Richardson sobre el trapecio, con i subintervalos
    // de ancho h (y 2i de ancho h/2 dentro de richardson).
    // En x = 0 la integral vale 0 (evita la división 0/0 con nrect = 0).
    const double I_num = (i == 0)
        ? 0.0
        : richardson(0.0, x, i, alpha, trapezoid, integrand);

    std::println("{:.16e} {:.16e} {:.16e}", x, I_exact, I_num);
  }

  return 0;
}


// Integrando: f(x) = 2 sin(x) + 2 x cos(x)
double integrand(double x)
{
  return 2.0 * std::sin(x) + 2.0 * x * std::cos(x);
}

// Primitiva exacta con V(0) = 0: V(x) = 2 x sin(x)
double exact_integral(double x)
{
  return 2.0 * x * std::sin(x);
}

// Regla del trapecio compuesta con nrect subintervalos (código del profesor).
//   ∫ f dx ≈ dx [ f(a)/2 + f(a+dx) + ... + f(b-dx) + f(b)/2 ]
double trapezoid(double a, double b, int nrect, fptr f)
{
  double dx = (b-a)/nrect;
  double suma = 0.0;
  suma = suma + f(a)/2;
  suma = suma + f(b)/2;
  for(int k = 1; k <= nrect-1; k++) {
    double xk = a + k*dx;
    suma = suma + f(xk);
  }
  return suma*dx;
}

// Extrapolación de Richardson (código del profesor).
// Si el algoritmo base I tiene error O(dx^alpha), se calcula con nrect y con
// 2*nrect subintervalos (paso dx y dx/2) y se cancela el término dominante:
//   I_R = [2^alpha * I(2 nrect) - I(nrect)] / (2^alpha - 1)
// Para el trapecio (alpha = 2) esto es [4 I2 - I1]/3, error O(dx^4).
double richardson(double a, double b, int nrect, int alpha, algintptr I, fptr f)
{
  double aux = std::pow(2.0, alpha);
  double val1 = I(a, b, nrect, f);      // paso dx
  double val2 = I(a, b, 2*nrect, f);    // paso dx/2
  return (aux*val2 - val1)/(aux-1);
}