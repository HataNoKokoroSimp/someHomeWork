#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

const int maxN = 1000;

int n, m;
long long arr[maxN][maxN];
long long vert[maxN][maxN];/// vertical
long long hori[maxN][maxN];/// horizontal
long long sum, mi, res;

int main()
{
    freopen("sum.inp", "r", stdin);
    freopen("sum.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    int i, j;

    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            cin >> arr[i][j];

    for(i = 0; i < n; i++)
    {
        sum = mi = 0;
        for(j = 0; j < m; j++)
        {
            sum += arr[i][j];
            hori[i][j] = sum - mi;
            mi = min(sum, mi);
        }

        sum = mi = 0;
        for(j = m - 1; j >= 0; j--)
        {
            sum += arr[i][j];
            hori[i][j] = max(hori[i][j], sum - mi);
            mi = min(mi, sum);
        }
    }

    for(j = 0; j < m; j++)
    {
        sum = mi = 0;
        for(i = 0; i < n; i++)
        {
            sum += arr[i][j];
            vert[i][j] = sum - mi;
            mi = min(sum, mi);
        }

        sum = mi = 0;
        for(i = n - 1; i >= 0; i--)
        {
            sum += arr[i][j];
            vert[i][j] = max(vert[i][j], sum - mi);
            mi = min(mi, sum);
        }
    }

    res = arr[0][0];
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            res = max(res, vert[i][j] + hori[i][j] - arr[i][j]);

    cout << res;
    return 0;
}
