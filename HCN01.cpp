#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

const int maxN = 1000;

int n, m, tmp;
int h[maxN + 1][maxN + 1];
int pre[maxN + 1];
stack<int> helper;

int res;
int main()
{
    freopen("HCN01.INP", "r", stdin);
    freopen("HCN01.OUT", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> m >> n;

    int i, j;
    for(i = 1; i <= m; i++)
        for(j = 1; j <= n; j++)
        {
            cin >> h[i][j];
            if(h[i][j] == 1)
                h[i][j] += h[i - 1][j];
        }

    res = 0;
    for(i = 1; i <= n; i++)
    {
        while(!helper.empty())
            helper.pop();

        for(j = 1; j <= n; j++)
        {
            while(!helper.empty())
            {
                if(h[i][helper.top()] < h[i][j])
                    break;
                helper.pop();
            }

            pre[j] = (helper.empty() ? 0 : helper.top());
            helper.push(j);
        }

        while(!helper.empty())
            helper.pop();

        for(j = n; j > 0; j--)
        {
            while(!helper.empty())
            {
                if(h[i][helper.top()] < h[i][j])
                    break;
                helper.pop();
            }

            tmp = (helper.empty() ? n + 1 : helper.top());
            res = max(res, h[i][j] * (tmp - pre[j] - 1));
            helper.push(j);
        }
    }

    cout << res;
    return 0;
}
