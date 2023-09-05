#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int maxN = 300000;

int n;
vector<int> edge[maxN];

int depth[maxN], pre[maxN];
int mDep1[maxN], mDep2[maxN];
int dia1[maxN], dia2[maxN];

void dfs1(const int &pos, const int &par)
{
    for(vector<int>::iterator edgeIter = edge[pos].begin(); edgeIter != edge[pos].end(); edgeIter++)
        if(*edgeIter != par)
        {
            depth[*edgeIter] = depth[pos] + 1;
            dfs1(*edgeIter, pos);
        }
}

void dfs2(const int &pos, const int &par)
{
    pre[pos] = par;
    mDep1[pos] = depth[pos];
    dia1[pos] = 1;

    int tmp1, tmp2;
    tmp1 = tmp2 = depth[pos];

    for(vector<int>::iterator edgeIter = edge[pos].begin(); edgeIter != edge[pos].end(); edgeIter++)
        if(*edgeIter != par)
        {
            depth[*edgeIter] = depth[pos] + 1;
            dfs2(*edgeIter, pos);
            mDep1[pos] = max(mDep1[pos], mDep1[*edgeIter]);
            dia1[pos] = max(dia1[pos], dia1[*edgeIter]);

            if(tmp1 < mDep1[*edgeIter])
            {
                tmp2 = tmp1;
                tmp1 = mDep1[*edgeIter];
            }
            else if(tmp2 < mDep1[*edgeIter])
                tmp2 = mDep1[*edgeIter];
        }

    dia1[pos] = max(dia1[pos], tmp1 + tmp2 - (depth[pos] << 1) + 1);
}

void dfs3(const int &pos, const int &par)
{
    mDep2[pos] = depth[pos];
    dia2[pos] = 1;

    int tmp1, tmp2;
    tmp1 = tmp2 = depth[pos];
    for(vector<int>::iterator edgeIter = edge[pos].begin(); edgeIter != edge[pos].end(); edgeIter++)
        if(*edgeIter != par)
        {
            depth[*edgeIter] = depth[pos] + 1;
            dfs3(*edgeIter, pos);

            mDep2[pos] = max(mDep2[pos], mDep2[*edgeIter]);
            dia2[pos] = max(dia2[pos], dia2[*edgeIter]);

            if(tmp1 < mDep2[*edgeIter])
            {
                tmp2 = tmp1;
                tmp1 = mDep2[*edgeIter];
            }
            else if(tmp2 < mDep2[*edgeIter])
                tmp2 = mDep2[*edgeIter];
        }
    dia2[pos] = max(dia2[pos], tmp1 + tmp2 - (depth[pos] << 1) + 1);
}

int tu, tv;
bool inDia[maxN];

int main()
{
    freopen("build.inp", "r", stdin);
    ///freopen("build.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;

    int i, p, tmp;
    for(i = 1; i < n; i++)
    {
        cin >> tu >> tv;
        tu--; tv--;

        edge[tu].push_back(tv);
        edge[tv].push_back(tu);
    }

    p = 0; depth[0] = 1; dfs1(0, -1);
    for(i = 1; i < n; i++)
        if(depth[i] > depth[p])
            p = i;

    depth[p] = 1;
    dfs2(p, -1); p = 0;
    for(i = 1; i < n; i++)
        if(depth[i] > depth[p])
            p = i;

    memset(inDia, 0x00, sizeof(inDia));
    tmp = p;
    while(tmp != -1)
    {
        inDia[tmp] = true;
        tmp = pre[tmp];
    }

    depth[p] = 1;
    dfs3(p, -1);

    vector<int>::iterator edgeIter;
    int res = 1;
    for(i = 0; i < n; i++)
    {
        for(edgeIter = edge[i].begin(); edgeIter != edge[i].end(); edgeIter++)
        {
            ///if edge on diameter
            if(inDia[i] && inDia[*edgeIter])
            {
                if(depth[i] < depth[*edgeIter])
                {
                    res = max(res, dia1[i] + dia2[*edgeIter]);
                    ///cout << i << ' ' << *edgeIter << ' ' << dia1[i] << ' ' << dia2[*edgeIter] << " 1 \n";
                }
            }
            else if(depth[i] < depth[*edgeIter])
            {
                res = max(res, dia1[*edgeIter] + dia2[p]); ///not in diameter
                ///cout << i << ' ' << *edgeIter << ' ' << dia2[*edgeIter] << ' ' << dia2[p] << " 2 \n";
            }
        }
    }

    cout << res - 1;
    return 0;
}
