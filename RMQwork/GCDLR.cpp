#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

#define FILE_IO

int n, l, r, p, q, lim;
std::vector<std::vector<int> > arr;
int main()
{
    #ifdef FILE_IO
        freopen("GCDLR.INP", "r", stdin);
        freopen("GCDLR.OUT", "w", stdout);
    #endif // FILE_IO

    std::cin >> n >> q;
    arr.push_back({});
    for(int i = 0; i < n; ++i)
    {
        std::cin >> p;
        arr.back().push_back(p);
    }

    lim = 1;
    for(int i = 1; (1 << i) <= n; ++i)
    {
        lim <<= 1;
        p = (lim >> 1);

        arr.push_back({});
        for(int j = 0; j + lim <= n; ++j)
            arr.back().push_back(std::__gcd(arr[i - 1][j], arr[i - 1][j + p]));
    }

    while(q)
    {
        std::cin >> l >> r;

        lim = r - l + 1;
        p = -1;
        while(lim)
        {
            p++;
            lim >>= 1;
        }

        std::cout << std::__gcd(arr[p][l - 1], arr[p][r - (1 << p)]) << '\n';
        q--;
    }
    return 0;
}
