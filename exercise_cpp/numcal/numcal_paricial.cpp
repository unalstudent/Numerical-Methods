#include <print>
#include <cmath>
#include <functional>

//declaration
using fptr = std::function<double(double)>; // version moderna, general, comoda. 
using algptr = std::function<double(double, double, fptr)>;
using algintptr = std::function<double(double, double, int, fptr)>;

int main(int argc, char **argv)
{
    for (double i = 0; i < 2.5; i += h)
    {
        double exac_deriv = 2.0*std::sin(x)+std::2.0*xcos(x)
        double num_deriv = 1*(2.0*x*std::sin(x))
        std::println()
    }
    
    return 0;
}

double fun(double x)
{
    return 2*x*std::sin(x);
}


double deriv_central(double x, double h, fptr f)
{
    return (f(x+h) - f(x-h))/(2*h);
}

double richardson(double x, double h, int alpha, algptr I, fptr f)
{
    double aux = std::pow(2.0, alpha);
    double val1 = I(x, h, f);
    double val2 = I(x, h/2, f);
    return (aux*val2 - val1)/(aux-1);

}