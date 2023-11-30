#include <bits/stdc++.h>

using namespace std;
const int maxN = 1005;
pair<long long, long long> arr[maxN];
int n, m;

long long pow2(const long long &num)
{
    return num * num;
}

long long cal_dis(const pair<long long, long long> &a, const pair<long long, long long> &b)
{
    return pow2(a.first - b.first) + pow2(a.second - b.second);
}

int col[maxN], deg[maxN];
void init(const long long &mdis)
{
    for(int i = 1; i <= n; i++)
    {
        deg[i] = 0;
        col[i] = -1;
    }
    deg[0] = 0;

    for(int i = 1; i <= n; i++)
        for(int j = i + 1; j <= n; j++)
            if(cal_dis(arr[i], arr[j]) < mdis)
                {deg[i]++; deg[j]++;}
}

bool pos_cmp(const int &a, const int &b)
{
    return deg[a] > deg[b];
}

int pos_l[maxN], pos_l_si;
bool can_choose[maxN];
bool color_graph(const long long &mdis)
{
    int has_col = 0;
    for(int i = 1; i <= m; i++)
    {
        pos_l_si = 0;
        for(int j = 1; j <= n; j++)
        {
            can_choose[j] = (col[j] == -1);
            if(can_choose[j])
            {
                pos_l[pos_l_si] = j;
                pos_l_si++;
            }
        }
        sort(pos_l, pos_l + pos_l_si, pos_cmp);

        for(int j = 0; j < pos_l_si; j++)
            if(can_choose[pos_l[j]])
            {
                col[pos_l[j]] = i;
                for(int k = 0; k < pos_l_si; k++)
                    if(j != k && cal_dis(arr[pos_l[j]], arr[pos_l[k]]) < mdis)
                        {deg[pos_l[k]]--; can_choose[pos_l[k]] = false;}
                has_col++;
            }
    }
    return (has_col == n);
}

int main()
{
    if(fopen("COLORING.INP", "r"))
    {
        freopen("COLORING.INP", "r", stdin);
        freopen("COLORING.OUT", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> arr[i].first >> arr[i].second;

    long long l = 0, r = 1e13, mid, res;
    while(l <= r)
    {
        mid = ((l + r) >> 1);

        init(mid);
        if(color_graph(mid))
        {
            l = mid + 1LL;
            res = mid;
        }
        else r = mid - 1;
    }

    color_graph(res);
    for(int i = 1; i <= n; i++)
        cout << col[i] << ' ';
    return 0;
}
