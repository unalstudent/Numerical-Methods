/*
The first 5 square numbers are: 1 4 9 16 25,
and the sum of the odd squares is 9+1+25=35
Among the first 435 thousand square numbers, what is the sum of all the odd squares?
*/

#include <print>
#include <functional>
//declaration

long long sum_odd_squares(long long n);

int main()
{
    
    std::println("the sum of al the odd squares is {}" , sum_odd_squares(217500));

    return 0;

}


long long sum_odd_squares(long long n)
{

return ((4 * n * n * n )- n) / 3;


}