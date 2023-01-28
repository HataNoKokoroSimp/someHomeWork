#include <iostream>
#include <cstdio>
#include <vector>

#define FILE_IO

int n, p, l, r, res, lim, tmp;
std::vector<std::vector<int> > arr;
int main()
{
    #ifdef FILE_IO
        freopen("CITY.INP", "r", stdin);
        freopen("CITY.OUT", "w", stdout);
    #endif // FILE_IO

    std::cin >> n;

    arr.push_back({});
    for(int i = 0; i < n; ++i)
    {
        std::cin >> p;
        arr.back().push_back(p);
    }

    lim = 1;
    for(int i = 1; (1 << i) <= n; ++i)
    {
        p = lim;
        lim <<= 1;

        arr.push_back({});
        for(int j = 0; j + lim <= n; ++j)
            arr.back().push_back(std::min(arr[i - 1][j], arr[i - 1][j + p]));
    }

    res = n;
    for(int i = 0; i < n; ++i)
    {
        l = 0, r = i - 1;
        lim = r - l + 1;
        p = 0;

        while(l <= r)
        {
            if(lim & (1 << p))
            {
                if(arr[p][r - (1 << p) + 1] <= arr[0][i])
                {
                    tmp = arr[p][r - (1 << p) + 1];
                    while(p)
                    {
                        p--;
                        if(arr[p][r - (1 << p) + 1] <= arr[0][i])
                            tmp = arr[p][r - (1 << p) + 1];
                        else r = r - (1 << p);
                    }
                    break;
                }
            }
            else r = r - (1 << p);
        }
        if(tmp == arr[0][i])
            res--;
    }
    std::cout << res;
    return 0;
}
