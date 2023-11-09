#include <bits/stdc++.h>

using namespace std;

const int maxN = 51;
const int maxM = 15;

long long dp[1 << maxM];
bitset<55> visited[1 << maxM][maxM];
int n, m;
vector<pair<int, long long> > state_l[maxM];
vector<long long> salery[maxM];

int dfs_dp(const int &state)
{
    if(dp[state] != -1)
        return dp[state];

    int max_pos = -1;
    for(int i = 0; i < m; i++)
        if((state >> i) & 1)
        {
            if(max_pos == -1)
                max_pos = i;
            else
            {
                if(salery[i].back() > salery[max_pos].back())
                    max_pos = i;
            }
        }

    for(vector<pair<int, long long> >::iterator iter = state_l[max_pos].begin(); iter != state_l[max_pos].end(); iter++)
        if((state & iter->first) == iter->first)
        {
            if(dfs_dp(state ^ iter->first) != -1)
            {
                if(dp[state] == -1)
                    dp[state] = dfs_dp(state ^ iter->first) + iter->second;
                else dp[state] = min(dp[state], dfs_dp(state ^ iter->first) + iter->second);
            }
        }
    return dp[state];
}

long long sum[maxM];
vector<vector<int> > edge[maxM][maxM];
vector<int>::iterator edge_iter;
int d;

struct bfs_info
{
    int group;
    int employ;
    int state;
    long long sale;

    bfs_info(){group = employ = state = 0; sale = 0;};
    bfs_info(const int &group, const int &employ, const int &state, const long long &sale)
    {this->group = group; this->employ = employ; this->state = state; this->sale = sale;}

};

struct cmp
{
    bool operator()(const bfs_info &a, const bfs_info &b)
    {
        return a.sale > b.sale;
    }
};

priority_queue<bfs_info, vector<bfs_info>, cmp> helper;
bfs_info tmp_info;
int tmp_state;
void bfs_loop(const int &st)
{
    helper.push(bfs_info(st, salery[st].size() - 1, (1 << st), salery[st].back()));

    for(int j = 0; j < m; j++)
        for(int i = 0; i < (1 << m); i++)
            visited[i][j].reset();

    while(!helper.empty())
    {
        tmp_info = helper.top();
        helper.pop();

        if(visited[tmp_info.state][tmp_info.group][tmp_info.employ])
            continue;
        visited[tmp_info.state][tmp_info.group][tmp_info.employ] = true;

        ///cout << "Go " << tmp_info.group << ' ' << tmp_info.employ << ' ' << tmp_info.sale << '\n';

        if(!edge[tmp_info.group][st][tmp_info.employ].empty())
        {
            if(edge[tmp_info.group][st][tmp_info.employ].back() == salery[st].size() - 1)
                state_l[st].push_back(make_pair(tmp_info.state, tmp_info.sale));
        }

        for(int i = 0; i < m; i++)
        {
            if((tmp_info.state >> i) & 1)
                continue;
            tmp_state = (tmp_info.state | (1 << i));
            for(edge_iter = edge[tmp_info.group][i][tmp_info.employ].begin(); edge_iter != edge[tmp_info.group][i][tmp_info.employ].end(); edge_iter++)
                helper.push(bfs_info(i, *edge_iter, tmp_state, salery[i][*edge_iter] + tmp_info.sale));
        }
    }
}

int main()
{
    freopen("leaders.inp", "r", stdin);
    freopen("leaders.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(dp, 0xFF, sizeof(dp)); dp[0] = 0;
    cin >> m >> n;

    for(int i = 0; i < m; i++)
    {
        cin >> d;
        salery[i].resize(d);

        sum[i] = 0;
        for(int j = 0; j < d; j++)
        {
            cin >> salery[i][j];
            sum[i] += salery[i][j];
        }
        sort(salery[i].begin(), salery[i].end());
    }

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            edge[i][j].resize(salery[i].size());
            for(int k = 0; k < salery[i].size(); k++)
                for(int h = 0; h < salery[j].size(); h++)
                    if(sum[j] - salery[j][h] <= salery[i][k])
                        edge[i][j][k].push_back(h);
        }
    }

    for(int i = 0; i < m; i++)
        bfs_loop(i);

    cout << dfs_dp((1 << m) - 1);
    return 0;
}
