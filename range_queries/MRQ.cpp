#include <vector>

template<typename T>
class MRQ
{
public:
    MRQ(const std::vector<T>& base_arr):
        baseArrSize(base_arr.size()), Tree(4 * base_arr.size())
    {
        __build(base_arr, 1, 0, baseArrSize - 1);
    }
    T query(int l, int r)
    {
        return __query(1, 0, baseArrSize - 1, l, r);
    }
    void update(int i, int new_val)
    {
        __update(1, 0, baseArrSize - 1, i, new_val);
    }
private:
    int baseArrSize;
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
        __build(base_arr, 2*v+1, tm+1, tr);
        Tree[v] = std::max(Tree[2*v], Tree[2*v+1]);
    }
    T __query(int v, int tl, int tr, int l, int r)
    {
        if(tl == l && tr == r)
        {
            return Tree[v];
        }
        if(l > r)
        {
            return 0;
        }
        int tm = (tl+tr)/2;
        return std::max(__query(2*v, tl, tm, l, std::min(r, tm)), __query(2*v+1, tm+1, tr, std::max(l, tm+1), r));
    }
    void __update(int v, int tl, int tr, int i, int new_val)
    {
        if(tl == tr)
        {
            Tree[v] = new_val;
            return;
        }
        int tm = (tl + tr)/2;
        if(i <= tm)
        {
            __update(2*v, tl, tm, i, new_val);
        }
        else
        {
            __update(2*v+1, tm+1, tr, i, new_val);
        }
        Tree[v] = max(Tree[2*v], Tree[2*v+1]);
    }

};
