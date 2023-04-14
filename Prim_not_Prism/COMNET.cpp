#include <iostream>
#include <cstring>
#include <cstdio>
#include <list>

struct position
{
    short x;
    short y;
};

int n, m, pX, pY, res;
position pos1, pos2;

int main()
{
    freopen("COMNET.INP", "r", stdin);
    freopen("COMNET.OUT", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> m >> n;

    std::list<position> adj[m][n];
    std::list<position>::iterator adjIter;

    while(std::cin >> pos1.x >> pos1.y >> pos2.x >> pos2.y)
    {
        pos1.x--; pos1.y--;
        pos2.x--; pos2.y--;

        adj[pos1.x][pos1.y].push_back(pos2);
        adj[pos2.x][pos2.y].push_back(pos1);
    }

    int8_t d[m][n];
    memset(d, 0x01, sizeof(d));

    res = 0;
    for(int i1 = 0; i1 < m; ++i1)
        for(int j1 = 0; j1 < n; ++j1)
        {
            pX = 0; pY = 0;
            for(int i = 0; i < m; ++i)
                for(int j = 0; j < n; ++j)
                    if(d[pX][pY] > d[i][j])
                    {
                        pX = i;
                        pY = j;
                    }

            if(d[pX][pY] == 1)
                res++;
            d[pX][pY] = 2;

            for(adjIter = adj[pX][pY].begin(); adjIter != adj[pX][pY].end(); adjIter++)
                if(d[adjIter->x][adjIter->y] != 2)d[adjIter->x][adjIter->y] = 0;
        }

    if(res == 1)
        std::cout << "YES";
    else
        std::cout << "NO\n" << res - 1;
    return 0;
}
