#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

///Why lots of maths appear in this test
long long n, k;
long long res, tmp;
int main()
{
    freopen("BSEQ.INP", "r", stdin);
    freopen("BSEQ.OUT", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> k;
    long long arr[n];

    for(long long i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
        arr[i] = arr[i] - i*k;
    }
    std::sort(arr, arr + n);

    res = 0;
    tmp = arr[(n >> 1)];
    for(int i = 0; i < n; ++i)
        res = res + std::abs(arr[i] - tmp);
    std::cout << res;
    return 0;
}
///Fumo coder
