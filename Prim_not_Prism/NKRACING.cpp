#include <iostream>
#include <cstring>
#include <cstdio>
#include <list>

int n, m, u, v;
int w, res;
int main()
{
    freopen("NKRACING.INP", "r", stdin);
    freopen("NKRACING.OUT", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> m;

    std::list<std::pair<int, int> > adj[n];
    std::list<std::pair<int, int> >::iterator adjIter;

    res = 0;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        u--; v--;

        res += w;
        adj[u].push_back(std::make_pair(v, w));
        adj[v].push_back(std::make_pair(u, w));
    }

    bool visited[n]; memset(visited, 0x00, sizeof(visited));
    int d[n]; memset(d, 0xFF, sizeof(d));

    d[0] = 0;
    for(int i = 0; i < n; ++i)
    {
        u = 0;
        for(int j = 1; j < n; ++j)
        {
            if(visited[j])
                continue;
            if(d[u] < d[j] || visited[u])
                u = j;
        }

        res -= d[u];
        visited[u] = true;

        for(adjIter = adj[u].begin(); adjIter != adj[u].end(); adjIter++)
            if(d[adjIter->first] < adjIter->second)
                d[adjIter->first] = adjIter->second;
    }

    std::cout << res;
    return 0;
}
