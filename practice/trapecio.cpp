// trapecio.cpp
// Integral por la regla del trapecio compuesta (función del profesor).
//
// Problema: dado el integrando
//   f(x) = dV/dx = 2 sin(x) + 2 x cos(x)
// recuperar V(x) = ∫_0^x f(t) dt, cuyo valor exacto es V(x) = 2 x sin(x).
//
// El paso h = Δx se lee de la línea de comandos. Para cada x = i*h en
// 0 <= x <= 2.5 se integra de 0 a x con i subintervalos de ancho h.
// Salida en pantalla, tres columnas (notación científica, 16 decimales):
//   x    valor exacto    valor numérico
//
// Compilar y ejecutar:
//   g++-14 -std=c++23 -O2 -Wall -Wextra trapecio.cpp -o trapecio.x && ./trapecio.x 0.02

#include <cstdlib>     // std::atof, std::lround
#include <cmath>       // std::sin, std::cos
#include <functional>  // std::function
#include <print>       // std::println (C++23)

// fptr: cualquier objeto invocable con firma double(double)
using fptr = std::function<double(double)>;

double integrand(double x);
double exact_integral(double x);
double trapezoid(double a, double b, int nrect, fptr f);


int main(int argc, char **argv)
{
  if (argc < 2) {
    std::println(stderr, "Uso: {} h", argv[0]);
    return 1;
  }

  const double h    = std::atof(argv[1]);  // paso h = Δx
  const double xmax = 2.5;

  // Número de pasos en la región (se redondea para evitar problemas de
  // punto flotante al dividir xmax / h).
  const int N = static_cast<int>(std::lround(xmax / h));

  for (int i = 0; i <= N; ++i) {
    const double x = i * h;  // límite superior de la integral

    // Valor exacto: ∫_0^x (2 sin t + 2 t cos t) dt = 2 x sin x
    const double I_exact = exact_integral(x);

    // Valor numérico: trapecio con i subintervalos de ancho h.
    // En x = 0 no hay intervalo (nrect = 0 daría una división 0/0 en
    // trapezoid), y la integral vale 0, así que se asigna directamente.
    const double I_num = (i == 0) ? 0.0 : trapezoid(0.0, x, i, integrand);

    // {:.16e} = notación científica con 16 decimales
    std::println("{:.16e} {:.16e} {:.16e}", x, I_exact, I_num);
  }

  return 0;
}


// Integrando: f(x) = dV/dx = 2 sin(x) + 2 x cos(x)
double integrand(double x)
{
  return 2.0 * std::sin(x) + 2.0 * x * std::cos(x);
}

// Primitiva exacta con V(0) = 0: V(x) = 2 x sin(x)
double exact_integral(double x)
{
  return 2.0 * x * std::sin(x);
}

// Regla del trapecio compuesta de f en [a, b] con nrect subintervalos
// (código del profesor). Error global O(dx^2).
//   ∫ f dx ≈ dx [ f(a)/2 + f(a+dx) + ... + f(b-dx) + f(b)/2 ]
double trapezoid(double a, double b, int nrect, fptr f)
{
  double dx = (b-a)/nrect;          // ancho de cada subintervalo
  double suma = 0.0;
  suma = suma + f(a)/2;             // extremo izquierdo con peso 1/2
  suma = suma + f(b)/2;             // extremo derecho con peso 1/2
  for(int k = 1; k <= nrect-1; k++) {
    double xk = a + k*dx;           // puntos interiores
    suma = suma + f(xk);            // con peso 1
  }
  return suma*dx;
}