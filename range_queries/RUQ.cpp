#include <vector>
template<typename T>
class RUQ
{
public:
    RUQ(const std::vector<T>& base_arr):
        base_arr_sz(base_arr.size()), Tree(4* base_arr.size())
    {
        __build(base_arr, 1, 0, base_arr_sz - 1); 
    }
    void update(int l, int r, T chg)
    {
        __update(1, 0, base_arr_sz - 1, l, r, chg);
    }
    int query(int i) const
    {
        return __query(1, 0, base_arr_sz - 1, i);
    }

private:
    int base_arr_sz;
    std::vector<T> Tree;
    void __build(const std::vector<T>& base_arr, int v, int tl, int tr)
    {
        if(tl == tr)
        {
            Tree[v] = base_arr[tl];
            return;
        }
        int tm = (tl + tr)/2;
        __build(base_arr, 2*v, tl, tm);
        __build(base_arr, 2*v+1, tm+1,tr);
    }
    int __query(int v, int tl, int tr, int i) const
    {
        if(tl == tr)
        {
            return Tree[v];
        }
        int tm = (tl + tr)/2;
        if(i <= tm)
        {
            return Tree[v] + __query(2*v, tl, tm, i);
        }
        else
        {
            return Tree[v] + __query(2*v+1, tm+1, tr, i);
        }
    }
    void __update(int v, int tl, int tr, int l, int r, int chg)
    {
        if(tl == l && tr == r)
        {
            Tree[v] += chg;
            return;
        }
        if(l > r)
        {
            return;
        }
        int tm = (tl + tr)/2;
        __update(2*v, tl, tm, l, std::min(r, tm), chg);
        __update(2*v+1, tm+1, tr, std::max(l, tm+1), r, chg);
    }
};
