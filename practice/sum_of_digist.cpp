#include <print>
#include <cmath>

long long sum_of_digits(long long a);

//declaration

int main(int argc, char const *argv[])
{
    long long  reslut = sum_of_digits(pow(2, 4));
    std::print("la suma de los digitos de {} es {}", pow(2, 4), reslut);
    return 0;
}


//implementation

long long sum_of_digits(long long a){
    long long total = 0;
    long long i = a;
    while ( i > 0)
    {
           total += i % 10;

         i = i/10;
    }
    return total;
}