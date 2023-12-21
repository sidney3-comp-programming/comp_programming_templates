#include "../RMQ.cpp"
#include <vector>

template<typename T>
T brute_force_maximum(std::vector<T> arr, int l, int r)
{
    assert(l <= r);
    assert(r < arr.size());
    T max_val = arr[l];
    for(int i = l; i <= r; i++)
    {
        max_val = (arr[i] > max_val) ? arr[i] : max_val;
    }
    return max_val;
}
void static_range_max_query()
{
    std::vector<int> arr = {5,4,3,2,1};
    RMQ<int, std::greater<int>> range_max(arr);
    
    for(size_t r = 0; r < arr.size(); r++)
    {
        for(size_t l = 0; l <= r; l++)
        {
            assert(brute_force_maximum<int>(arr, l, r) == range_max.query(l,r));
        }
    }
}
