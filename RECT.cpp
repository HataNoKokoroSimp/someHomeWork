#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

const int maxN = 5e5;

int n, m, now;
int h[maxN + 1];
stack<int> yellow, blue;
int yelpre[maxN + 1], blupre[maxN + 1];

long long res;
int main()
{
    freopen("RECT.INP", "r", stdin);
    freopen("RECT.OUT", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> m >> n;
    for(int i = 1; i <= n; i++)
        cin >> h[i];

    for(int i = 1; i <= n; i++)
    {
        while(!yellow.empty())
        {
            if(h[yellow.top()] < h[i])
                break;
            yellow.pop();
        }

        while(!blue.empty())
        {
            if(h[blue.top()] > h[i])
                break;
            blue.pop();
        }

        yelpre[i] = (yellow.empty() ? 0 : yellow.top());
        blupre[i] = (blue.empty() ? 0 : blue.top());

        yellow.push(i); blue.push(i);
    }

    while(!yellow.empty())
        yellow.pop();
    while(!blue.empty())
        blue.pop();

    res = 0;
    for(int i = n; i > 0; i--)
    {
        while(!yellow.empty())
        {
            if(h[yellow.top()] < h[i])
                break;
            yellow.pop();
        }

        now = (yellow.empty() ? n + 1 : yellow.top());
        res = max(res, (long long)h[i] * (long long)(now - yelpre[i] - 1));

        while(!blue.empty())
        {
            if(h[blue.top()] > h[i])
                break;
            blue.pop();
        }

        now = (blue.empty() ? n + 1 : blue.top());
        res = max(res, (long long)(m - h[i]) * (long long)(now - blupre[i] - 1));

        yellow.push(i); blue.push(i);
    }

    cout << res;

    return 0;
}
