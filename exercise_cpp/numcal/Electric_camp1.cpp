// field.cpp
// Campo eléctrico a partir del potencial: E_x = -dV/dx, con V(x) = 2 x sin(x)
// en la región 0 <= x <= 2.5.
//
// La derivada se calcula con diferencias centrales mejoradas con
// extrapolación de Richardson. El paso h = Δx se lee de la línea de comandos
// y los resultados se escriben en pantalla en tres columnas:
//   x    valor exacto    valor numérico      (notación científica, 16 decimales)
//
// Compilar y ejecutar:
//   g++ -std=c++23 -O2 -Wall -Wextra field.cpp -o field.x && ./field.x 0.02

#include <cstdlib>     // std::atof
#include <cmath>       // std::sin, std::cos
#include <functional>  // std::function
#include <print>       // std::print / std::println (C++23, reemplaza a <iostream>)

// fptr: cualquier objeto invocable con firma double(double)
// (función, lambda, functor...). std::function lo envuelve de forma uniforme.
using fptr = std::function<double(double)>;

double potential(double x);
double dev_central(double x, double h, fptr fun);
template <typename algptr>
double dev_richardson(double x, double h, fptr fun, algptr algo);


int main(int argc, char **argv)
{
  // Se necesita el paso h como argumento
  if (argc < 2) {
    std::println(stderr, "Uso: {} h", argv[0]);
    return 1;
  }

  // Paso h = Δx leído de la línea de comandos
  const double h = std::atof(argv[1]);

  for (double x = 0.0; x <= 2.5; x += h) {
    // Valor exacto del campo: E = -dV/dx = -(2 sin x + 2 x cos x)
    const double E_exact = -(2.0 * std::sin(x) + 2.0 * x * std::cos(x));

    // Valor numérico: Richardson aplicado a la derivada central de V.
    // Se pasa dev_central como algoritmo base; el signo menos viene de E = -dV/dx.
    const double E_num = -dev_richardson(x, h, potential, dev_central);

    // {:.16e} = notación científica con 16 decimales (ej: 1.0000000000000001e-01)
    std::println("{:.16e} {:.16e} {:.16e}", x, E_exact, E_num);
  }

  return 0;
}


// Potencial eléctrico: V(x) = 2 x sin(x)
double potential(double x)
{
  return 2.0 * x * std::sin(x);
}

// Derivada central de fun en x con paso h (error O(h^2)):
//   fun'(x) ≈ [fun(x+h) - fun(x-h)] / (2h)
double dev_central(double x, double h, fptr fun)
{
  return (fun(x + h) - fun(x - h)) / (2.0 * h);
}

// Extrapolación de Richardson sobre un algoritmo de derivada `algo`
// (aquí, la derivada central). Con D(h) = algo(x, h, fun), el error es
// c2*h^2 + c4*h^4 + ... Combinando D(h/2) y D(h/4) se cancela el término h^2:
//   D_R = [4 D(h/4) - D(h/2)] / 3        (error O(h^4))
// Es la misma combinación que en 2.cpp. `algo` es un parámetro de plantilla,
// así que sirve con cualquier método con firma (x, h, fun).
template <typename algptr>
double dev_richardson(double x, double h, fptr fun, algptr algo)
{
  const double D1 = algo(x, h / 2.0, fun);
  const double D2 = algo(x, h / 4.0, fun);
  return (4.0 * D2 - D1) / 3.0;
}