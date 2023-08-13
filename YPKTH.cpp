#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

const int maxN = 1e5;
int n, q;

vector<int> f[maxN << 2];
int arr[maxN + 1];

void mer(const int &id)
{
    f[id].resize(f[id*2].size() + f[id*2+1].size());
    merge(f[id*2].begin(), f[id*2].end(), f[id*2+1].begin(), f[id*2+1].end(), f[id].begin());
}

void build(const int &id, const int &l, const int &r)
{
    if(r < l)
        return;

    if(l == r)
    {
        f[id].clear();
        f[id].push_back(arr[l]);
        return;
    }

    int mid = ((l + r) >> 1);

    build(id*2, l, mid);
    build(id*2+1, mid+1, r);

    mer(id);

    /*cout << id << ' ' << l << ' ' << r << ":\n";
    for(int i = 0; i < f[id].size(); ++i)
        cout << f[id][i] << ' ';
    cout << '\n';*/
}

int getLow(const int &id, const int &l, const int &r, const int &u, const int &v, const int &val)
{
    if(r < l)
        return 0;

    if(v < l || r < u)
        return 0;

    if(u <= l && r <= v)
        return (upper_bound(f[id].begin(), f[id].end(), val) - f[id].begin());

    int mid = ((l + r) >> 1);
    return getLow(id*2, l, mid, u, v, val) + getLow(id*2+1, mid+1, r, u, v, val);
}

map<int, int> helper;
int main()
{
    freopen("YPKTH.INP", "r", stdin);
    freopen("YPKTH.OUT", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;

    for(int i = 1; i <= n; ++i)
        cin >> arr[i];

    build(1, 1, n);

    int l, r, k, nl, nr, mid, tmp, res;
    cin >> q;
    while(q--)
    {
        cin >> l >> r >> k;

        nl = -1e9; nr = 1e9;
        while(nl <= nr)
        {
            mid = ((nl + nr) >> 1);

            tmp = getLow(1, 1, n, l, r, mid);

            if(tmp == k)
                res = mid;

            if(tmp >= k)
                nr = mid - 1;
            else if(tmp < k)
                nl = mid + 1;
        }
        cout << res << '\n';
    }

    return 0;
}
