#include <vector>
#include <cmath>
#include <concepts>

template<typename T, typename Callable>
class SparseTable
{
public:
    SparseTable(const std::vector<T>& base_arr):
        base_arr_sz(base_arr.size()), LOG(log2(base_arr_sz)),
        range_table(std::vector<std::vector<T>>(LOG + 1, std::vector<int>(base_arr_sz))),
        log_table(base_arr_sz + 1), comparator(Callable())
    {
        __build_log_table();
        __build_range_table(base_arr);
    }
    T operator()(int l, int r) const
    {
        int diff = r - l + 1;
        int diff_log = log_table[diff];
        T l_component = range_table[diff_log][l];
        T r_component = range_table[diff_log][r - (1<<(diff_log)) + 1];
        return (comparator(l_component, r_component)) ? l_component : r_component;
    }
private:
    const int base_arr_sz;
    const int LOG;
    std::vector<std::vector<T>> range_table;
    std::vector<int> log_table;
    const Callable comparator;
    void __build_log_table()
    {
        log_table[0] = 1;
        for(int i = 1; i <= base_arr_sz; i++)
        {
            log_table[i] = (log2(i));
        }
    }
    void __build_range_table(const std::vector<T>& base_arr)
    {
        for(size_t i = 0; i < base_arr.sz(); i++)
        {
            range_table[0][i] = base_arr[i];
        }
        for(int pow = 1; pow <= LOG; pow++)
        {
            for(size_t i = 0; i < base_arr.sz(); i++)
            {
                T l_component = range_table[pow-1][i];
                int r_component_begin = i + (1<<(pow-1));
                T r_component = range_table[pow-1][std::min(r_component_begin, base_arr_sz - 1)];
                range_table[pow][i] = (comparator(l_component, r_component)) ? l_component : r_component; 
            }
        }
    }
};
