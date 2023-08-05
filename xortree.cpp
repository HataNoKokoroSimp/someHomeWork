#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int maxN = 100000;

///seg tree

int f[maxN << 2];

void pDown(const int &id)
{
    f[id*2] ^= f[id];
    f[id*2+1] ^= f[id];

    f[id] = 0;
}

void update(const int &id, const int &l, const int &r, const int &u, const int &v, const int &val)
{
    if(r < l)
        return;

    if(v < l || r < u)
        return;

    if(u <= l && r <= v)
    {
        f[id] ^= val;
        return;
    }

    pDown(id);

    int mid = ((l + r) >> 1);
    update(id*2, l, mid, u, v, val);
    update(id*2+1, mid+1, r, u, v, val);
}

int getVal(const int &id, const int &l, const int &r, const int &pos)
{
    if(r < l)
        return 0;

    if(pos < l || r < pos)
        return 0;

    if(l == r)
        return f[id];

    pDown(id);

    int mid = ((l + r) >> 1);
    return (getVal(id*2, l, mid, pos) ^ getVal(id*2+1, mid+1, r, pos));
}

///dfs
int tim = -1;
int tin[maxN];
int tout[maxN];
vector<int> edge[maxN];

void dfs(const int &pos, const int &parent)
{
    tim++;
    tin[pos] = tim;
    for(int i = 0; i < edge[pos].size(); ++i)
        if(edge[pos][i] != parent)
            dfs(edge[pos][i], pos);

    tout[pos] = tim;
}

///main
int n, q, fu, fv;
int tu[maxN], tv[maxN], c[maxN];
char typ;
int main()
{
    freopen("xortree.inp", "r", stdin);
    freopen("xortree.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> q;
    for(int i = 1; i < n; ++i)
    {
        cin >> tu[i] >> tv[i] >> c[i];
        tu[i]--; tv[i]--;

        edge[tu[i]].push_back(tv[i]);
        edge[tv[i]].push_back(tu[i]);
    }

    dfs(0, -1);
    for(int i = 1; i < n; ++i)
    {
        if(tin[tu[i]] < tin[tv[i]])
            update(1, 0, n - 1, tin[tv[i]], tout[tv[i]], c[i]);
        else
            update(1, 0, n - 1, tin[tu[i]], tout[tu[i]], c[i]);
    }

    while(q--)
    {
        cin >> typ >> fu >> fv;
        if(typ == '1')
        {
            if(tin[tu[fu]] < tin[tv[fu]])
                update(1, 0, n - 1, tin[tv[fu]], tout[tv[fu]], fv ^ c[fu]);
            else update(1, 0, n - 1, tin[tu[fu]], tout[tu[fu]], fv ^ c[fu]);
            c[fu] = fv;
        }
        else
        {
            fu--; fv--;
            cout << (getVal(1, 0, n - 1, tin[fu])  ^ getVal(1, 0, n - 1, tin[fv])) << '\n';
        }
    }

    return 0;
}
