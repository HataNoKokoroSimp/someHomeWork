#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>

using namespace std;

const int maxN = 1e6;
const int maxP = 1e5;

namespace BITree
{
    void add(int *st, const int &si, const int &val, int pos)
    {
        pos++;
        while(pos <= si)
        {
            *(st + pos - 1) += val;
            pos += (pos & (-pos));
        }
    }

    int tmpSum;
    int getSum(int *st, int pos)
    {
        pos++;
        tmpSum = 0;

        while(pos)
        {
            tmpSum += *(st + pos - 1);
            pos ^= (pos & (-pos));
        }
        return tmpSum;
    }
}

int m, n, p, q;
int f[maxN + 1];

int d;
pair<pair<int, int>, bool> arr[maxP * 5];
map<pair<int, int>, int> cal;
int x[maxP], y[maxP], u[maxP], v[maxP];

int main()
{
    freopen("tree.inp", "r", stdin);
    freopen("tree.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> m >> n >> p >> q;

    for(int i = 0; i < p; i++)
    {
        cin >> arr[i].first.first >> arr[i].first.second;
        arr[i].second = false;
    }

    d = p;
    for(int i = 0; i < q; i++)
    {
        cin >> x[i] >> y[i] >> u[i] >> v[i];

        arr[d].first.first = u[i]; arr[d].first.second = v[i]; arr[d].second = true; d++;
        arr[d].first.first = u[i]; arr[d].first.second = y[i] - 1; arr[d].second = true; d++;
        arr[d].first.first = x[i] - 1; arr[d].first.second = v[i]; arr[d].second = true; d++;
        arr[d].first.first = x[i] - 1; arr[d].first.second = y[i] - 1; arr[d].second = true; d++;
    }

    sort(arr, arr + d);
    memset(f, 0x00, sizeof(f));
    for(int i = 0; i < d; i++)
    {
        if(arr[i].second)
        {
            cal.insert(make_pair(arr[i].first, BITree::getSum(f, arr[i].first.second)));
        }
        else
        {
            BITree::add(f, n, 1, arr[i].first.second);
        }
    }

    for(int i = 0; i < q; i++)
    {
        cout << cal[make_pair(u[i], v[i])] + cal[make_pair(x[i] - 1, y[i] - 1)]
              - cal[make_pair(u[i], y[i] - 1)] - cal[make_pair(x[i] - 1, v[i])] << '\n';
    }
    return 0;
}
