#include <print>

//decalaration
long long multiply(long long a, long long b, long long limite);


int main(int argc, char const *argv[])
{
    long long a = 3, b = 5;
    long long limite = 1000;

    std::println("la suma de los multiplos de {} y {} es {}", a, b, multiply(a, b, limite));

}



//implemetation


long long multiply(long long a, long long b, long long limite){
    long long suma = 0;
 for (long long i = a; i < limite; i++)
 {
     if ( i % a == 0 or i % b == 0)
    {
        suma += i; 
    }
    
}
return suma;
}
 