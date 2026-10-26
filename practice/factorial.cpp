#include <print>


//declaration

long long factorial(long long n);
long long sumofdigits(long long a);

int main(int argc, char const *argv[])
{
    long long lol = factorial(5);
    long long lal = sumofdigits(lol);
    std::print("{}", lal);
    return 0;
}
 

//implementation

long long factorial(long long n){
    long long resultado = 1;
    for (long long i = 2; i <= n; i++)
    {
    resultado *= i ;
    }
 return resultado;   
}

long long sumofdigits(long long a){
    long long total = 0;
    long long i = a;
    while ( i > 0)
    {
           total += i % 10;

         i = i/10;
    }
    return total;
}