// 2.cpp
// Campo eléctrico a partir del potencial eléctrico: E_x = -dV/dx
// con V(x) = 2 x sin(x) en la región 0 <= x <= 2.5.
//
// La derivada se calcula con diferencias centrales y se mejora con
// extrapolación de Richardson. Compilar con:
//   g++ -std=c++23 -O2 -Wall -Wextra 2.cpp -o 2.x && ./2.x

#include <fstream>
#include <cmath>

// ----------------------------------------------------------------------
// Prototipos (según la plantilla)
// ----------------------------------------------------------------------
double potential(double x);
double dev_central(double x, double h);
double dev_central_richardson(double x, double h);
double electricfield(double x, double h);

int main(void)
{
  // Parámetros del problema
  constexpr double h    = 0.02;  // paso de la derivada, h = Δx = 0.02
  constexpr double xmin = 0.0;   // límite inferior de la región
  constexpr double xmax = 2.5;   // límite superior de la región

  // Número de pasos. Se redondea para evitar problemas de punto flotante
  // al dividir (xmax - xmin) / h.
  const int N = static_cast<int>(std::lround((xmax - xmin) / h));

  // Archivo de salida
  std::ofstream fout("campo.txt");

  // Formato científico con 16 decimales (ej: 1.0000000000000001e-01)
  fout.setf(std::ios::scientific);
  fout.precision(16);

  double x = xmin;
  for (int i = 0; i <= N; ++i, x += h) {
    // x se avanza sumando h en cada iteración (x += h), como en el
    // archivo de referencia.

    // Valor exacto del campo: E = -dV/dx = -(2 sin x + 2 x cos x)
    const double E_exact = -(2.0 * std::sin(x) + 2.0 * x * std::cos(x));

    // Valor numérico del campo (Richardson sobre la derivada central)
    const double E_num = electricfield(x, h);

    // Columnas: x, valor exacto, valor numérico
    fout << x << "\t" << E_exact << "\t" << E_num << "\n";
  }

  fout.close();
  return 0;
}

// ----------------------------------------------------------------------
// Potencial eléctrico: V(x) = 2 x sin(x)
// ----------------------------------------------------------------------
double potential(double x)
{
  return 2.0 * x * std::sin(x);
}

// ----------------------------------------------------------------------
// Derivada central de V en x con paso h:
//   V'(x) ≈ [V(x+h) - V(x-h)] / (2h)      (error O(h^2))
// ----------------------------------------------------------------------
double dev_central(double x, double h)
{
  return (potential(x + h) - potential(x - h)) / (2.0 * h);
}

// ----------------------------------------------------------------------
// Extrapolación de Richardson sobre la derivada central.
// Sea D(h) la derivada central. Su error es  c2*h^2 + c4*h^4 + ...
// Combinando D(h/2) y D(h/4) se cancela el término h^2:
//   D_R = [4 D(h/4) - D(h/2)] / 3          (error O(h^4))
// (aquí h es el paso base Δx = 0.02; las derivadas centrales internas
// usan h/2 y h/4, que es lo que reproduce los valores de campo.txt)
// ----------------------------------------------------------------------
double dev_central_richardson(double x, double h)
{
  const double D1 = dev_central(x, h / 2.0);  // paso h/2
  const double D2 = dev_central(x, h / 4.0);  // paso h/4
  return (4.0 * D2 - D1) / 3.0;
}

// ----------------------------------------------------------------------
// Campo eléctrico: E_x = -dV/dx, usando la derivada con Richardson
// ----------------------------------------------------------------------
double electricfield(double x, double h)
{
  return -dev_central_richardson(x, h);
}