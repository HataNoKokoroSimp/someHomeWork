#include <bits/stdc++.h>

using namespace std;
const int maxN = 205;

int n, f[maxN], res;
long long arr[maxN];
int main()
{
    if(fopen("DIVSET.INP", "r"))
    {
        freopen("DIVSET.INP", "r", stdin);
        freopen("DIVSET.OUT", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    sort(arr + 1, arr + n + 1);

    res = 0;
    for(int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for(int j = 1; j < i; j++)
            if(arr[i] % arr[j] == 0 && f[i] <= f[j])
                f[i] = f[j] + 1;
        if(res < f[i]) res = f[i];
    }
    cout << res;
    return 0;
}
