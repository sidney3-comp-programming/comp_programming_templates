#include <vector>
#include <utility>
#include <concepts>

/**
  * A purer sort of segment tree
  *
  *
**/
template <std::floating_point T, 
         template<typename, typename...> class Container,
         typename Callable>
class SegTree
{
public:
    SegTree(const Container<T>& base_arr, const Callable& _join):
        base_arr_sz(base_arr.size()), Tree(4*base_arr.size()), join(_join)
    {
        __build(base_arr);
    }
    void update(int i, T new_val)
    {
        __update(1, 0, base_arr_sz - 1, i, new_val);
    }
    T query(int l, int r)
    {
        return __query(1, 0, base_arr_sz - 1, l, r);
    }
    T query(int i)
    {
        return __query(1, 0, base_arr_sz - 1, i, i);
    }
private:
    const int base_arr_sz;
    std::vector<T> Tree;
    Callable join;
    void __build(const Container<T> base_arr, int v, int tl, int tr)
    {
        if(tl == tr)
        {
            Tree[v] = base_arr[tl];
        }
        else
        {
            int tm = (tl + tr)/2;
            __build(base_arr, 2*v, tl, tm);
            __build(base_arr, 2*v+1, tm+1, tr);
            Tree[v] = join(Tree[2*v], Tree[2*v+1]);
        }
    }
    void __build(const Container<T> base_arr)
    {
        __build(base_arr, 1, 0, base_arr_sz - 1);
    }
    void __update(int v, int tl, int tr, int i, T new_val)
    {
        if(tl == tr)
        {
            Tree[v] = new_val;
        }
        else
        {
            int tm = (tl + tr)/2;
            if(i <= tm)
            {
                __update(2*v, tl, tm, i, new_val);
            }
            else
            {
                __update(2*v+1, tm+1, tr, i, new_val);
            }
            Tree[v] = join(Tree[2*v], Tree[2*v+1]);
        }
    }
    void __query(int v, int tl, int tr, int l, int r)
    {
        if(tl == l && tr == r)
        {
            return Tree[v];
        }
        int tm = (tl + tr)/2;
        std::pair<int,int> left_child = std::make_pair(l, std::min(r, tm));
        std::pair<int,int> right_child = std::make_pair(std::max(tm+1,l), r);
        // As we have no default value for the more generic segment tree, we must be a bit less clever
        if(left_child.first > left_child.second)
        {
            return __query(2*v+1, tm+1,tr,right_child.first, right_child.second);
        }
        else if(right_child.first > right_child.second)
        {
            return __query(2*v, tl, tm, left_child.first, left_child.second);
        }
        else
        {
            return join(__query(2*v, tl, tm, left_child.first, left_child.second),
                        __query(2*v+1, tm+1, tr, right_child.first, right_child.second));
        }
    }
};
