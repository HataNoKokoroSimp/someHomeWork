#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <climits>

///binary search
///but still maths
const int maxN = 100000;

int n;
std::pair<double, double> arr[maxN];
bool chooseSub;

void sub1()
{
    double xLen = (arr[n-1].first - arr[0].first)/2.0f;
    double yLen = arr[0].second;
    std::cout << sqrt(xLen*xLen + yLen*yLen);
}

const double lrDiff = 0.000000000001f;
void sub2()
{
    double l = arr[0].first, r = arr[n-1].first;
    double mid;

    double res = 100000000000LL;

    int maPos;
    double maDis, dis;
    while(r - l >= lrDiff)
    {
        maPos = 0;
        mid = (l + r)/2.0f;
        maDis = -1;

        for(int i = 0; i < n; ++i)
        {
            dis = mid - arr[i].first;
            dis = sqrt(dis*dis + arr[i].second*arr[i].second);

            if(dis > maDis)
            {
                maDis = dis;
                maPos = i;
            }
        }

        res = std::min(res, maDis);

        if(arr[maPos].first == mid)
        {
            std::cout << res;
            return;
        }
        if(arr[maPos].first < mid)
            r = mid - lrDiff;
        else l = mid + lrDiff;
    }
    std::cout << res;
}

int main()
{
    freopen("SAMSONTH.INP", "r", stdin);
    freopen("SAMSONTH.OUT", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n;

    chooseSub = true;
    for(int i = 0; i < n; ++i)
    {
        std::cin >> arr[i].first >> arr[i].second;
        if(arr[i].second != arr[0].second)
            chooseSub = false;
    }

    std::sort(arr, arr + n);

    std::cout << std::fixed << std::setprecision(6);
    if(chooseSub)sub1();
    else sub2();

    return 0;
}
///Fumo coder
