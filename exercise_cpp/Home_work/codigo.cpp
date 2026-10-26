#include <fstream>
#include <functional>
#include <iostream>
#include <print>
#include <string>
#include <vector>

// declaracion

typedef std::function<double(double)> fptr;

// variables globales: la pdf del histograma, para poder usarla como función de x
std::vector<double> fpdf;
double gxmin;
double gdx;

// lee todas las muestras del archivo
std::vector<double> read_samples(std::string fname);

// mínimo y máximo de las muestras
double minimum(const std::vector<double> &xdata);
double maximum(const std::vector<double> &xdata);

// histograma de conteo: h[i] = número de muestras en la caja i
std::vector<double> histogram(const std::vector<double> &xdata, double xmin, double dx, int N);

// pdf: f = h/(S*dx)
std::vector<double> compute_pdf(const std::vector<double> &h, int S, double dx);

// pdf del histograma como función de x: devuelve f de la caja donde cae x
double pdf_hist(double x);

// integral de f entre a y b con la regla del trapecio
double trapezoid(double a, double b, int nrect, fptr f);

// cdf: F(x_i) = integral de la pdf desde xmin hasta x_i (x_i = centro de la caja i)
std::vector<double> compute_cdf(double xmin, double dx, int N);

// escribe x, f(x), F(x) en un archivo
void write_stats(std::string fname, double xmin, double dx,
                 const std::vector<double> &f, const std::vector<double> &F);


int main(int argc, char **argv)
{
    // revisar que se pasaron el archivo y N
    if (argc != 3) {
        std::println("Uso: ./a.out samples.txt <N>");
        return 1;
    }
    std::string fname = argv[1];
    int N = std::stoi(argv[2]);          // número de cajas

    // 1. leer las muestras
    std::vector<double> xdata = read_samples(fname);
    int S = xdata.size();                // número total de muestras
    if (S == 0) {
        std::println("No se pudieron leer muestras de {}", fname);
        return 1;
    }

    // 2. mínimo, máximo y ancho de cada caja
    double xmin = minimum(xdata);
    double xmax = maximum(xdata);
    double dx = (xmax - xmin)/N;

    // 3. histograma y pdf
    std::vector<double> h = histogram(xdata, xmin, dx, N);
    std::vector<double> f = compute_pdf(h, S, dx);

    // 4. guardar la pdf en las variables globales y calcular la cdf
    fpdf = f;
    gxmin = xmin;
    gdx = dx;
    std::vector<double> F = compute_cdf(xmin, dx, N);

    // 5. escribir stats.txt
    write_stats("stats.txt", xmin, dx, f, F);

    return 0;
}


// implementacion

std::vector<double> read_samples(std::string fname)
{
    std::vector<double> xdata;
    std::ifstream fin(fname);
    double x;
    while (fin >> x) {
        xdata.push_back(x);
    }
    fin.close();
    return xdata;
}

double minimum(const std::vector<double> &xdata)
{
    int n = xdata.size();
    double xmin = xdata[0];
    for (int k = 0; k < n; k++) {
        if (xdata[k] < xmin) xmin = xdata[k];
    }
    return xmin;
}

double maximum(const std::vector<double> &xdata)
{
    int n = xdata.size();
    double xmax = xdata[0];
    for (int k = 0; k < n; k++) {
        if (xdata[k] > xmax) xmax = xdata[k];
    }
    return xmax;
}

std::vector<double> histogram(const std::vector<double> &xdata, double xmin, double dx, int N)
{
    int S = xdata.size();
    std::vector<double> h(N, 0.0);
    for (int k = 0; k < S; k++) {
        int i = (xdata[k] - xmin)/dx;    // se trunca a entero
        if (i == N) {
            i = N - 1;                   // la muestra x = xmax va en la última caja
        }
        h[i] = h[i] + 1;
    }
    return h;
}

std::vector<double> compute_pdf(const std::vector<double> &h, int S, double dx)
{
    int N = h.size();
    std::vector<double> f(N);
    for (int i = 0; i < N; i++) {
        f[i] = h[i]/(S*dx);
    }
    return f;
}

double pdf_hist(double x)
{
    int N = fpdf.size();
    int i = (x - gxmin)/gdx;             // caja donde cae x
    if (i >= N) {
        i = N - 1;
    }
    return fpdf[i];
}

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

std::vector<double> compute_cdf(double xmin, double dx, int N)
{
    std::vector<double> F(N);
    for (int i = 0; i < N; i++) {
        double x = xmin + (i + 0.5)*dx;  // centro de la caja i
        int nrect = 100*(i + 1);         // rectángulos del trapecio
        F[i] = trapezoid(xmin, x, nrect, pdf_hist);
    }
    return F;
}

void write_stats(std::string fname, double xmin, double dx,
                 const std::vector<double> &f, const std::vector<double> &F)
{
    int N = f.size();
    std::ofstream fout(fname);
    for (int i = 0; i < N; i++) {
        double x = xmin + (i + 0.5)*dx;  // centro de la caja i
        std::println(fout, "{} {} {}", x, f[i], F[i]);
    }
    fout.close();
}