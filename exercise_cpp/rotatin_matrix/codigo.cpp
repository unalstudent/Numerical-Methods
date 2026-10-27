#include <print>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>  
#include <cassert> 

// Alias para simplificar el codigo 
using Vec = std::vector<double>; 

// Declaración de funciones (operaciones matriciales y rotaciones)
Vec rotation_x(double theta);
Vec rotation_y(double theta);
Vec rotation_z(double theta);
Vec matvec(const Vec &A, int m, int n, const Vec &v);
Vec rotate(const Vec &v, double thetax, double thetay, double thetaz);

int main(int argc, char const *argv[])
{
    // Verificación de los 6 argumentos
    if (argc != 7){
        std::println("no suficientes argumentos");
        return 1; 
    }

    const double vx     = std::stod(argv[1]);
    const double vy     = std::stod(argv[2]);
    const double vz     = std::stod(argv[3]);
    const double thetax = std::stod(argv[4]);
    const double thetay = std::stod(argv[5]);
    const double thetaz = std::stod(argv[6]);

    Vec v = {vx, vy, vz};

    const auto Rx = rotation_x(thetax);
    const auto Ry = rotation_y(thetay);
    const auto Rz = rotation_z(thetaz);

    // Aplicación secuencial de las rotaciones y print de la matriz
    const Vec v_rot = rotate(v, thetax, thetay, thetaz);
    std::println("{:g} {:g} {:g}", v_rot[0], v_rot[1], v_rot[2]);

    return 0;
}


// implementation


//matriz de rotación alrededor del eje X
Vec rotation_x(double theta) {
  const int n = 3;
  Vec R(n * n, 0.0);

  const double c = std::cos(theta);
  const double s = std::sin(theta);

  R[0 * n + 0] = 1.0;
  R[1 * n + 1] = c;
  R[1 * n + 2] = -s;
  R[2 * n + 1] = s;
  R[2 * n + 2] = c;

  return R;
}

//matriz de rotación alrededor del eje Y
Vec rotation_y(double theta){
    const int n = 3; 
    Vec R(n * n, 0.0);

    const double c = std::cos(theta);
    const double s = std::sin(theta);
  
    R[0 * n + 0] = c;
    R[0 * n + 2] = s;
    R[1 * n + 1] = 1.0;
    R[2 * n + 0] = -s; 
    R[2 * n + 2] = c;

    return R;
}

// matriz de rotación alrededor del eje Z
Vec rotation_z(double theta) {
  const int n = 3;
  Vec R(n * n, 0.0);

  const double c = std::cos(theta);
  const double s = std::sin(theta);

  R[0 * n + 0] = c;
  R[0 * n + 1] = -s;
  R[1 * n + 0] = s;
  R[1 * n + 1] = c;
  R[2 * n + 2] = 1.0;

  return R;
}

// Multiplicación de matriz (m x n) por vector
Vec matvec(const Vec &A, int m, int n, const Vec &v) {

  assert(static_cast<int>(v.size()) == n);

  Vec result(m, 0.0);

  for (int ii = 0; ii < m; ++ii) {
    for (int jj = 0; jj < n; ++jj) {
      result[ii] += A[ii * n + jj] * v[jj];
    }
  }

  return result;
}

// se multiplican en este ordenn X -> Y -> Z
Vec rotate(const Vec &v, double thetax, double thetay, double thetaz) {
  const Vec after_x = matvec(rotation_x(thetax), 3, 3, v);
  const Vec after_y = matvec(rotation_y(thetay), 3, 3, after_x);
  return matvec(rotation_z(thetaz), 3, 3, after_y);
}

    /*
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡶⠒⠓⢆⡀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠞⠁⠀⠀⠀⠈⡆⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡴⠋⠀⠀⠀⠀⠀⠈⡇⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡾⣁⠀⠀⠀⠀⠀⠀⠠⡇⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢯⠋⠀⢣⠀⠀⠀⠀⠀⢠⠁⠀⠀⠀⠀⠀⠀
    ⠐⢀⣀⠤⠤⠄⠄⣀⣀⡀⠀⣌⡍⡇⠀⠀⠀⠇⠀⠀⠀⠀⡸⠀⠀⠀⠀⠀⠀⠀
    ⠀⠸⣀⠀⠀⠀⠀⠀⠀⠀⠩⡏⢸⠃⠤⢀⠠⢢⠘⠒⠀⢀⠓⢢⠀⠀⠀⠀⠀⠀
    ⠀⠀⠈⠲⣀⠀⠀⠀⠀⢠⡟⡀⢼⠊⠀⡀⠀⢉⠐⠠⠄⡈⢠⠜⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠙⠲⢤⡠⣲⠀⠀⢼⠀⢿⣿⠆⠀⠂⡀⡤⠑⠉⠒⠠⡀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⢠⠊⠼⠝⠂⠤⣼⣀⠀⣁⣤⢴⠒⡉⠂⠀⠀⠀⠀⠀⠑⢄⠀⠀
    ⠀⠀⠀⠀⠀⠀⠰⠬⡞⠠⠤⠤⢜⡒⠉⠒⠲⠾⠤⣌⣀⠀⡀⠀⠀⠀⠀⠀⢸⠀
    ⠀⠄⠀⠀⠀⠀⠀⢸⠇⠀⠀⠀⠀⢅⠀⠀⠀⠆⠌⠀⠈⠈⠉⠉⠁⠛⠈⠉⠁⠀
    ⠀⠀⠀⠀⠀⠀⠀⣾⠀⠀⠀⠀⠀⠈⢂⠀⣘⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⡟⠀⠀⠀⠀⠀⠀⠀⢠⠊⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⡀⡰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⢿⠀⠀⠀⠀⡰⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠈⠳⠦⠞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    */