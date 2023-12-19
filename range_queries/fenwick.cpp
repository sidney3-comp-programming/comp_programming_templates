#include <vector>
#include <concepts>

template<typename T>
class Fenwick
{
public:
    Fenwick(const int base_arr_sz): T(base_arr_sz)
    {}
    void update(int i, T chg)
    {
        i++;
        while(i <= Tree.size())
        {
            Tree[i-1] += chg;
            i += (i&-i);
        }
    }
    long long query(int i)
    {
        i++;
        long long res = 0;
        while(i > 0)
        {
            res += Tree[i-1];
            i -= (i&-i);
        }
        return res;
    }
private:
    std::vector<T> Tree;
};
