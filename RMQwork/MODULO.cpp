#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

#define FILE_IO

int GCD(int a, int b)
{
    if(a == 0 || b == 0)
        return (a + b);
    return std::__gcd(a, b);
}

int n, l, r, p, q, lim;
std::vector<std::vector<int> > arr;
int main()
{
    #ifdef FILE_IO
        freopen("MODULO.INP", "r", stdin);
        freopen("MODULO.OUT", "w", stdout);
    #endif // FILE_IO

    std::cin >> n >> q;

    int data[n];
    for(int i = 0; i < n; ++i)
        std::cin >> data[i];

    arr.push_back({});
    for(int i = 1; i < n; ++i)
        arr.back().push_back(abs(data[i] - data[i - 1]));

    lim = 1;
    for(int i = 1; (1 << i) < n; ++i)
    {
        p = lim;
        lim <<= 1;

        arr.push_back({});
        for(int j = 0; j + lim < n; ++j)
            arr.back().push_back(GCD(arr[i - 1][j], arr[i - 1][j + p]));
    }

    while(q--)
    {
        std::cin >> l >> r;

        if(l == r)
        {
            std::cout << "-1\n";
            continue;
        }

        lim = r - l;
        p = -1;
        while(lim)
        {
            p++;
            lim >>= 1;
        }

        p = GCD(arr[p][l - 1], arr[p][r - (1 << p) - 1]);
        std::cout << ((p == 0) ? -1 : p) << '\n';
    }
    return 0;
}
