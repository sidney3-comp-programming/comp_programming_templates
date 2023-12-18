#include <vector>
std::vector<int> get_divisors(int x)
{
    std::vector<int> divisors;
    int x_sqrt = sqrt(x);
    for(int d = 1; d <= x_sqrt; d++)
    {
        if(x % d == 0)
        {
            divisors.push_back(d);
            if(x/d != d)
            {
                divisors.push_back(x/d);
            }
        }
    }
    return divisors;
}
