
int fast_pow(int x, int p, int md = (int) 1e9 + 7)
{
    if(p == 0)
    {
        return 1;
    }
    else if(p & 1)
    {
        return x * fast_pow(x, p - 1) % md;
    }
    int res = fast_pow(x, p/2) % md;
    return res*res;
}
