#include "multiply.h"

//implementacion

long long mulitply(long long a, long long b, long long my_limit){
    long long sum = 0;
    for (long long i = 3; i < my_limit; i += 1 ){
        if(i % a == 0 or i % b ==0){
            sum += i;
        }
    }
    return sum;
}

