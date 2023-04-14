#include <iostream>
#include <cstring>
#include <cstdio>

int n, u, v, res;
int main()
{
    freopen("WATER.INP", "r", stdin);
    freopen("WATER.OUT", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> n;

    int d[n];
    for(int i = 0; i < n; ++i)
        std::cin >> d[i];

    int cost[n][n];
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            std::cin >> cost[i][j];

    bool visited[n];
    memset(visited, 0x00, sizeof(visited));

    for(int i = 0; i < n; ++i)
    {
        u = 0;
        for(int j = 1; j < n; ++j)
        {
            if(visited[j])
                continue;
            if(visited[u])
                u = j;
            else u = ((d[u] > d[j]) ? j : u);
        }

        res = res + d[u];
        visited[u] = true;

        for(int j = 0; j < n; ++j)
            if(d[j] > cost[u][j])
                d[j] = cost[u][j];
    }

    std::cout << res;
    return 0;
}
