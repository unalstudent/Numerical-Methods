#include <print>

bool isprime(int m);
int nthprime(int n);

int main()
{
  const int n = 10001;
  std::println("{}", nthprime(n));

  return 0;
}

bool isprime(int m)
{
    // Esta funcion retorna true si m es primo, false en otro caso
    if (m <= 1) return false;

    for (int i = 2; i * i <= m; i++)
    {
        if (m % i == 0)
        {
            return false;
        }
    }
    return true;
}

int nthprime(int n)
{
    // esta funcion retorna el n-esimo primo, haciendo uso de isprime
    int count = 0;
    int candidate = 1;

    while (count < n)
    {
        candidate++;
        if (isprime(candidate))
        {
            count++;
        }
    }
    return candidate;
}