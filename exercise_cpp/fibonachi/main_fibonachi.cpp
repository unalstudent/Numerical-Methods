#include "fibonachi.h"
#include <print>


int main(){
    long long result = even_fibonachi(1, 2, 4000000);
    std::println("the 4 millon even number in the fibonachi sequance is {}", result);
}