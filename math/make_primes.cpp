#include <vector>

std::vector<int> make_primes(const int max_prime = (int) 1e7)
{
    std::vector<bool> is_prime(max_prime + 1, true);
    std::vector<int> primes;
    int max_prime_sqrt = sqrt(max_prime);
    for(int p = 2; p <= max_prime; p++)
    {
        if(!is_prime[p])
        {
            continue;
        }
        primes.push_back(p);
        for(int m = 2*p; m <= max_prime_sqrt; m += p)
        {
            is_prime[m] = false;
        }
    }
    return primes;
}
