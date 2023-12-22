#include <vector>
#include <stdexcept>
template<
    class T,
    class Container = std::vector<T>,
    class Join = std::less<T>
> class SegmentTree 
{
public:
    SegmentTree(const Container& base):
        _join(Join()), underlying_size(base.size()),
        tree(4 * base.size())
    {
        __build(base, 1, 0, underlying_size - 1);
    }
    void update(int l, int r, T new_val)
    {
        __update(1, 0, underlying_size - 1, l, r, new_val);
    }
    T query(int l, int r)
    {
        return __query(1, 0, underlying_size - 1, l, r);
    }
    T query(int i)
    {
        return __query(1, 0, underlying_size - 1, i, i);
    }
private:
    Join _join;
    int underlying_size;
    std::vector<T> tree;
    void __build(const Container& base, int v, int tl, int tr)
    {
        if(tl == tr)
        {
            tree[v] = base[tl];
        }
        else
        {
            int tm = (tl + tr)/2;
            __build(base, 2*v, tl, tm);
            __build(base, 2*v+1, tm+1, tr);
            tree[v] = _join(tree[2*v], tree[2*v+1]);
        }
    }
    void __update(int v, int tl, int tr, int l, int r, T new_val)
    {
        if(tl == l && tr == r)
        {
            tree[v] = new_val;
        }
        else if(l > r)
        {
            return;
        }
        else
        {
            int tm = (tl + tr)/2;
            __update(2*v, tl, tm, l, std::min(r, tm), new_val);
            __update(2*v+1, tm+1, tr, std::max(l, tm+1), r, new_val);
            tree[v] = _join(tree[2*v], tree[2*v+1]);
        }
    }
    T __query(int v, int tl, int tr, int l, int r)
    {
        if(tl == l && tr == r)
        {
            return tree[v];
        }
        else
        {
            int tm = (tl + tr)/2;
            int new_r = std::min(r, tm);
            int new_l = std::max(l, tm+1);
            /* assert(l <= new_r || new_l <= r); */
            if(l <= new_r && new_l <= r)
            {
                return _join(__query(2*v, tl, tm, l, new_r), __query(2*v+1, tm+1, tr, new_l, r));
            }
            else if(l <= new_r)
            {
                return __query(2*v, tl, tm, l, new_r);
            }
            else if(new_l <= r)
            {
                return __query(2*v+1, tm+1, tr, new_l, r);
            }
            else
            {
                throw std::invalid_argument("bad l,r values");
            }
        }
    }
};
