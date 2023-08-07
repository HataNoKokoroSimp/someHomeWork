#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

int n, q;
int s, b;

stack<int> helper;
int res = 0;
int main()
{
    freopen("guitar.inp", "r", stdin);
    freopen("guitar.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> q;

    for(int i = 0; i < q; ++i)
    {
        cin >> s >> b;

        while(!helper.empty())
        {
            if(helper.top() < b)
                break;

            helper.pop();
            res++;
        }

        helper.push(b);
        res++;
    }

    cout << res;
    return 0;
}
