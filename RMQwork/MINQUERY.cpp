#include <iostream>
#include <cstdio>
#include <vector>

#define FILE_IO

int n, q, lim, p;
int a, b;
std::vector<std::vector<int> > arr;
int main()
{
    #ifdef FILE_IO
        freopen("MINQUERY.INP", "r", stdin);
        freopen("MINQUERY.OUT", "w", stdout);
    #endif // FILE_IO

    std::cin >> n >> q;
    arr.push_back({});
    for(int i = 0; i < n; ++i)
    {
        std::cin >> p;
        arr[0].push_back(p);
    }

    lim = 1;
    for(int i = 1; (1 << i) <= n; ++i)
    {
        arr.push_back({});
        lim <<= 1;
        p = (lim >> 1);
        for(int j = 0; j + lim <= n; ++j)
            arr.back().push_back(std::min(arr[i - 1][j], arr[i - 1][j + p]));
    }

    while(q)
    {
        std::cin >> a >> b;
        lim = b - a + 1;

        p = -1;
        while(lim)
        {
            p++;
            lim >>= 1;
        }

        std::cout << std::min(arr[p][a - 1], arr[p][b - (1 << p)]) << '\n';
        q--;
    }
    return 0;
}
