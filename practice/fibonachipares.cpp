
//

//

long long even_fibonachi(long long a, long long b)
{
    while (a <= my_limit)
    {
        if (a % 2 == 0)
        {
            sum += a;
        }
        
        sequence = a + b;
        a = b;
        b = sequence;

    }
    return sum;
    
}