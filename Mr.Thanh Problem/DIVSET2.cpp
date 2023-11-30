#include <bits/stdc++.h>

using namespace std;
const int maxN = 205;

int n, f[maxN], res;
pair<long long, int> arr[maxN];
vector<vector<int> > group_l;

int main()
{
    if(fopen("DIVSET2.INP", "r"))
    {
        freopen("DIVSET2.INP", "r", stdin);
        freopen("DIVSET2.OUT", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr + 1, arr + n + 1);

    for(int i = 1; i <= n; i++)
    {
        f[i] = 1;
        for(int j = 1; j < i; j++)
            if(arr[i].first % arr[j].first == 0 && f[i] <= f[j])
                f[i] = f[j] + 1;
        if(res < f[i])res = f[i];
    }

    cout << res;
    group_l.resize(res);

    for(int i = 1; i <= n; i++)
        group_l[f[i] - 1].push_back(arr[i].second);
    for(int i = 0; i < res; i++)
    {
        cout << '\n';
        for(int j = 0; j < group_l[i].size(); j++)
            cout << group_l[i][j] << ' ';
    }
    return 0;
}
