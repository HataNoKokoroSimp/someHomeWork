#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int maxV = 5e5;

int v, e, q;
int res[maxV];

vector<pair<int, int> > edge[maxV];
vector<pair<int, int> >::iterator edgeIter;

struct dat
{
    int qual;
    int pos;

    dat()
    {
        qual = 1000000000;
        pos = 0;
    }

    dat(const int &v1, const int &v2)
    {
        qual = v1;
        pos = v2;
    }
};

struct cmp
{
    bool operator()(const dat &a, const dat &b)
    {
        return (a.qual < b.qual);
    }
};

priority_queue<dat, vector<dat>, cmp> helper;
dat tmpDat;

int tu, tv, tw;
int main()
{
    freopen("way.inp", "r", stdin);
    freopen("way.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> v >> e >> q;
    for(int i = 0; i < e; i++)
    {
        cin >> tu >> tv >> tw;
        tu--; tv--;

        edge[tu].push_back(make_pair(tv, tw));
        edge[tv].push_back(make_pair(tu, tw));
    }

    memset(res, 0xFF, sizeof(res));

    helper.push(dat());
    while(!helper.empty())
    {
        tmpDat = helper.top();
        helper.pop();

        if(res[tmpDat.pos] != -1)
            continue;
        res[tmpDat.pos] = tmpDat.qual;

        for(edgeIter = edge[tmpDat.pos].begin(); edgeIter != edge[tmpDat.pos].end(); edgeIter++)
            if(res[edgeIter->first] == -1)
                helper.push(dat(min(tmpDat.qual, edgeIter->second), edgeIter->first));
    }

    for(int i = 0; i < q; i++)
    {
        cin >> tu; tu--;
        cout << res[tu] << '\n';
    }
    return 0;
}
