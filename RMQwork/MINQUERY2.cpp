#include <iostream>
#include <cstdio>
#include <vector>

#define FILE_IO

int n, m, l1, r1, l2, r2;
int p, q, lim1, lim2, tmp1, tmp2;
std::vector<std::vector<std::vector<std::vector<int> > > > arr;
int main()
{
    #ifdef FILE_IO
        freopen("MINQUERY2.INP", "r", stdin);
        freopen("MINQUERY2.OUT", "w", stdout);
    #endif // FILE_IO
    /*std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);*/

    std::cin >> n >> m >> q;

    arr.push_back({});

    arr.back().push_back({});
    for(int i = 0; i < n; ++i)
    {
        arr.back().back().push_back({});
        for(int j = 0; j < m; ++j)
        {
            std::cin >> p;
            arr.back().back().back().push_back(p);
        }
    }

    lim2 = 1;
    for(int i = 1; (1 << i) <= m; ++i)
    {
        p = lim2;
        lim2 <<= 1;

        arr.back().push_back({});
        for(int j = 0; j < n; ++j)
        {
            arr.back().back().push_back({});
            for(int k = 0; k + lim2 <= m; ++k)
                arr.back().back().back().push_back(std::min(arr[0][i-1][j][k], arr[0][i-1][j][k+p]));
        }
    }

    lim1 = 1;
    for(int i = 1; (1 << i) <= n; ++i)
    {
        tmp1 = lim1;
        lim1 <<= 1;

        arr.push_back({});

        arr.back().push_back({});
        for(int k = 0; k + lim1 <= n; ++k)
        {
            arr.back().back().push_back({});
            for(int l = 0; l < m; ++l)
                arr.back().back().back().push_back(std::min(arr[i - 1][0][k][l], arr[i - 1][0][k+tmp1][l]));
        }

        lim2 = 1;
        for(int j = 1; (1 << j) <= m; ++j)
        {
            lim2 = (1 << j);
            tmp2 = (lim2 >> 1);

            arr.back().push_back({});
            for(int k = 0; k + lim1 <= n; ++k)
            {
                arr.back().back().push_back({});
                for(int l = 0; l + lim2 <= m; ++l)
                    arr.back().back().back().push_back(std::min(arr[i][j - 1][k][l], arr[i][j - 1][k][l + p]));
            }
        }
    }

    while(q)
    {
        std::cin >> l1 >> r1 >> l2 >> r2;

        if( (l1 > l2) || (r1 > r2) )
        {
            std::cout << "Ko bit noi gi!!!\n";
            q--;
            continue;
        }

        lim1 = l2 - l1 + 1;
        lim2 = r2 - r1 + 1;

        tmp1 = -1; tmp2 = -1;
        while(lim1){lim1 >>= 1; tmp1++;}
        while(lim2){lim2 >>= 1; tmp2++;}

        /*std::cout << tmp1 << ' ' << tmp2 << '\n';
        return 0;*/
        p = std::min(arr[tmp1][tmp2][l1 - 1][r1 - 1], arr[tmp1][tmp2][l2 - (1 << tmp1)][r2 - (1 << tmp2)]);
        p = std::min(p, arr[tmp1][tmp2][l1 - 1][r2 - (1 << tmp2)]);
        p = std::min(p, arr[tmp1][tmp2][l2 - (1 << tmp1)][r1 - 1]);
        std::cout << p << '\n';
        q--;
    }
    return 0;
}
