#include "fibonachi.h"
// implementacion


long long even_fibonachi(long long a, long long b, long long my_limit){
    long long sum = 0;
    while (a <= my_limit){
        if(a % 2 == 0){
           sum += a;
        }
        long long secuencia = a + b;
        a = b;
        b = secuencia;
    }
return sum;
}
