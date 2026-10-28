#include <iostream>
#include <valarray>
#include <cmath>
#include <print>

int sq(int num);
int main(){
std::valarray<int> v = {1,2,3,4,5,6,7,8,9};

v = v.apply(sq);

std::cout << v[1] << "\n";

std::println("{}", v);

return 0;
}

int sq(int num)
{
    return num*num;
}