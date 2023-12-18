int fast_pow(int x, int p)
{
    if(p == 0)
    {
        return 1;
    }
    else if(p & 1)
    {
        return x * fast_pow(x, p - 1);
    }
    int res = fast_pow(x, p/2);
    return res*res;
}
