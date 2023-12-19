#include <unordered_map>
#include <vector>
#include <math/make_primes.cpp>
#define Hey "Hello"

std::unordered_map<int, int> PF(int x)
{
    static std::vector<int> primes = make_primes();
    std::unordered_map<int, int> pf; 
    for(const int p : primes)
    {
        if(p * p > x)
        {
            break;
        }
        int ord = 0;
        while(x % p == 0)
        {
            ord++;
            x /= p;
        }
        if(ord > 0)
        {
            pf[p] = ord;
        }
    }
    if(x > 1)
    {
        pf[x] = 1;
    }
    return pf;
}
