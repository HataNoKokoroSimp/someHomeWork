#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define FILE_IO

struct data
{
    int l, r;
    int index;
};

std::vector<std::vector<int> > arr;

int getMaxLim, getMaxTmp;
int getMax(const int &l, const int &r)
{
    if(r < l)
        return -1;
    getMaxLim = r - l + 1;
    getMaxTmp = -1;
    while(getMaxLim)
    {
        getMaxLim >>= 1;
        getMaxTmp++;
    }
    return std::max(arr[getMaxTmp][l], arr[getMaxTmp][r - (1 << getMaxTmp) + 1]);
}

bool cmp(const data &a, const data &b)
{
    if((a.l == b.l) && (a.r == b.r))
        return (a.index < b.index);
    if((a.l >= b.l) && (a.r <= b.r))
        return true;
    if((a.l <= b.l) && (a.r >= b.r))
        return false;

    if(a.l < b.l)
        return (getMax(a.l, std::min(b.l - 1, a.r)) < getMax(std::max(a.r + 1, b.l), b.r));
    return (getMax(std::max(b.r + 1, a.l), a.r) < getMax(b.l, std::min(b.r, a.l - 1)));
}

int n, m, p;
int lim;
int main()
{
    #ifdef FILE_IO
        freopen("SORT.INP", "r", stdin);
        freopen("SORT.OUT", "w", stdout);
    #endif // FILE_IO
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); std::cout.tie(NULL);

    /**Read**/
    std::cin >> n >> m;

    arr.push_back({});
    for(int i = 0; i < n; ++i)
    {
        std::cin >> p;
        arr.back().push_back(p);
    }

    data query[m];
    for(int i = 0; i < m; ++i)
    {
        std::cin >> query[i].l >> query[i].r;
        query[i].l--;
        query[i].r--;
        query[i].index = i + 1;
    }

    /**Prepare Max Sparse Table**/

    lim = 1;
    for(int i = 1; (1 << i) <= n; ++i)
    {
        p = lim;
        lim <<= 1;

        arr.push_back({});
        for(int j = 0; j + lim <= n; ++j)
            arr.back().push_back(std::max(arr[i - 1][j], arr[i - 1][j + p]));
    }

    /**Make the compare function**/
    /// Of course, it isn't here
    /**-------------------------**/

    std::sort(query, query + n, cmp);

    for(int i = 0; i < m; ++i)
        std::cout << query[i].index << ' ';
    return 0;
}
