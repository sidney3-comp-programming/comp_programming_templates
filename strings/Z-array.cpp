#include <vector>

template<typename T>
std::vector<int> make_Z_array(std::vector<T> S)
{
    std::vector<int> Z(S.size());
    Z[0] = S.size();
    int L = 0, R = 0;
    for(int i = 1; i < S.size(); i++)
    {
        if(i > R)
        {
            L = R = i;
            while(R < S.size() && S[R] == S[R - L])
            {
                R++;
            }
            R--;
            Z[i] = R - L + 1;
        }
        else
        {
            int k = i - L;
            if(Z[k] < R - i + 1)
            {
                Z[i] = Z[k];
            }
            else
            {
                L = i;
                while(R < S.size() && S[R] == S[R-L])
                {
                    R++;
                }
                R--;
                Z[i] = R - L + 1;
            }
        }
    }
    return Z;
}
