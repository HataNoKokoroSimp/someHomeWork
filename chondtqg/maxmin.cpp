#include <iostream>
#include <cstdio>

using namespace std;

const int maxN = 2e5;

int arr[maxN];
int n, x, y;
int pa, px, py;

long long res;
int main()
{
    freopen("maxmin.inp", "r", stdin);
    freopen("maxmin.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> x >> y;

    int i;
    for(i = 0; i < n; i++)
        cin >> arr[i];

    px = py = pa = -1;
    for(i = 0; i < n; i++)
    {
        if(arr[i] < y || x < arr[i])
        {
            px = py = -1;
            pa = i;
            continue;
        }

        if(arr[i] == x)
            px = i;
        if(arr[i] == y)
            py = i;

        if(px != -1 && py != -1)
            res += (long long)(min(px, py) - pa);
    }

    cout << res;

    return 0;
}
