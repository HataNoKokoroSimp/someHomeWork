#include <iostream>
#include <cstdio>
#include <vector>

#define FILE_IO

const int maxN = 300000;
int n, p, lim, l, r, res;
std::vector<std::vector<int> > arr;

int main()
{
    #ifdef FILE_IO
        freopen("FIRST.INP", "r", stdin);
        freopen("FIRST.OUT", "w", stdout);
    #endif // FILE_IO
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    ///read data
    std::cin >> n;
    int data[n];
    arr.push_back({});
    for(int i = 0; i < n; ++i)
    {
        std::cin >> data[i];
        arr.back().push_back(i);
    }

    ///previous solve
    lim = 1;
    for(int i = 1; (1 << i) <= n; ++i)
    {
        p = lim;
        lim <<= 1;

        arr.push_back({});
        for(int j = 0; j + lim <= n; ++j)
        {
            if(data[arr[i - 1][j]] > data[arr[i - 1][j + p]])
                arr.back().push_back(arr[i - 1][j]);
            else arr.back().push_back(arr[i - 1][j + p]);
        }
    }

    ///solve
    for(int i = 0; i < n; ++i)
    {
        ///left
        l = 0, r = i - 1;
        lim = r - l + 1;
        p = 0;
        res = -2;
        while(l <= r)
        {
            if(lim & (1 << p))
            {
                if(data[arr[p][r - (1 << p) + 1]] > data[i])
                {
                    res = arr[p][r - (1 << p) + 1];
                    while(p)
                    {
                        p--;
                        if(data[arr[p][r - (1 << p) + 1]] > data[i])
                            res = arr[p][r - (1 << p) + 1];
                        else r = r - (1 << p);
                    }
                    break;
                }
                else r = r - (1 << p);
            }
            p++;
        }
        std::cout << res + 1<< ' ';

        ///right
        l = i + 1, r = n - 1;
        lim = r - l + 1;
        p = 0;
        res = -2;
        while(l <= r)
        {
            if(lim & (1 << p))
            {
                if(data[arr[p][l]] > data[i])
                {
                    res = arr[p][l];
                    while(p)
                    {
                        p--;
                        if(data[arr[p][l]] > data[i])
                            res = arr[p][l];
                        else l = l + (1 << p);
                    }
                    break;
                }
                else l = l + (1 << p);
            }
            p++;
        }
        std::cout << res + 1 << '\n';
    }
    return 0;
}
