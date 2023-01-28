#include <iostream>
#include <cstdio>
#include <vector>

#define FILE_IO

int n, lim, l, r;
std::vector<long long> arr;
std::vector<std::vector<long long> > miPos;
std::vector<std::vector<long long> > maPos;
long long maS, miS, p;
long long res[4];

int main()
{
    #ifdef FILE_IO
        freopen("SUMDIFF.INP", "r", stdin);
        freopen("SUMDIFF.OUT", "w", stdout);
    #endif // FILE_IO
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    /**Read data**/
    std::cin >> n;

    miPos.push_back({});
    maPos.push_back({});
    for(int i = 0; i < n; ++i)
    {
        std::cin >> p;
        arr.push_back(p);
        miPos.back().push_back(i);
        maPos.back().push_back(i);
    }

    /**Previous solve**/
    lim = 1;
    for(int i = 1; (1 << i) <= n; ++i)
    {
        p = lim;
        lim <<= 1;

        miPos.push_back({});
        maPos.push_back({});
        for(int j = 0; j + lim <= n; ++j)
        {
            if(arr[miPos[i - 1][j]] < arr[miPos[i - 1][j + p]])
                miPos.back().push_back(miPos[i - 1][j]);
            else miPos.back().push_back(miPos[i - 1][j + p]);

            if(arr[maPos[i - 1][j]] > arr[miPos[i - 1][j + p]])
                maPos.back().push_back(maPos[i - 1][j]);
            else maPos.back().push_back(maPos[i - 1][j + p]);
        }
    }

    /**Solve**/
    maS = miS = 0;
    for(long long i = 0; i < n; ++i)
    {
        ///left
            ///greater
            l = 0; r = i - 1;
            lim = r - l + 1;
            p = 0;
            res[0] = -1;

            while(l <= r)
            {
                if(lim & (1 << p))
                {
                    if(arr[maPos[p][r - (1 << p) + 1]] > arr[i])
                    {
                        res[0] = maPos[p][r - (1 << p) + 1];
                        while(p)
                        {
                            p--;
                            if(arr[maPos[p][r - (1 << p) + 1]] > arr[i])
                                res[0] = maPos[p][r - (1 << p) + 1];
                            else r = r - (1 << p);
                        }
                        break;
                    }
                    else r = r - (1 << p);
                }
                p++;
            }
            ///less
            l = 0, r = i - 1;
            lim = r - l + 1;
            res[1] = -1;
            p = 0;

            while(l <= r)
            {
                if(lim & (1 << p))
                {
                    if(arr[miPos[p][r - (1 << p) + 1]] < arr[i])
                    {
                        res[1] = miPos[p][r - (1 << p) + 1];
                        while(p)
                        {
                            p--;
                            if(arr[miPos[p][r - (1 << p) + 1]] < arr[i])
                                res[1] = miPos[p][r - (1 << p) + 1];
                            else r = r - (1 << p);
                        }
                        break;
                    }
                    else r = r - (1 << p);
                }
                p++;
            }
        ///right
            ///not less (greater or equal)
            l = i + 1, r = n - 1;
            lim = r - l + 1;
            p = 0;
            res[2] = n;
            while(l <= r)
            {
                if(lim & (1 << p))
                {
                    if(arr[maPos[p][l]] >= arr[i])
                    {
                        res[2] = maPos[p][l];
                        while(p)
                        {
                            p--;
                            if(arr[maPos[p][l]] >= arr[i])
                                res[2] = maPos[p][l];
                            else l = l + (1 << p);
                        }
                        break;
                    }
                    else l = l + (1 << p);
                }
                p++;
            }

            ///not greater(less or equal)
            l = i + 1, r = n - 1;
            lim = r - l + 1;
            p = 0; res[3] = n;
            while(l <= r)
            {
                if(lim & (1 << p))
                {
                    if(arr[miPos[p][l]] <= arr[i])
                    {
                        res[3] = miPos[p][l];
                        while(p)
                        {
                            p--;
                            if(arr[miPos[p][l]] <= arr[i])
                                res[3] = miPos[p][l];
                            else l = l + (1 << p);
                        }
                        break;
                    }
                    else l = l + (1 << p);
                }
                p++;
            }
        ///std::cout << res[0] << ' ' << res[1] << ' ' << res[2] << ' ' << res[3] << '\n';
        maS = maS + arr[i] * (i - res[0]) * (res[2] - i);
        miS = miS + arr[i] * (i - res[1]) * (res[3] - i);
    }
    std::cout << maS - miS;
    return 0;
}
