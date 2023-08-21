#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

const int maxN = 4e5;

long long res;
long long H, D, S;
int arr[maxN];
int n, T, tmp, tmp2;

deque<int> helper;
int work[maxN + 1];

int main()
{
    freopen("PROJECT.INP", "r", stdin);
    freopen("PROJECT.OUT", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    cin >> H >> S >> D;

    int i;
    for(i = 0; i < n; i++)
        cin >> arr[i];

    T = (H + D)/S;

    for(i = 0; i <= T; i++)
    {
        tmp = (i < n ? arr[i] : 0);
        while(!helper.empty())
        {
            tmp2 = (helper.back() < n ? arr[helper.back()] : 0);
            if(tmp2 > tmp)
                break;
            helper.pop_back();
        }

        helper.push_back(i);
    }

    work[0] = 0;
    for(i = 0; i < n; i++)
    {
        if(work[i] < arr[i])
        {
            res += ((long long)(arr[i] - work[i]) * H);
            work[i] = arr[i];
        }

        tmp = (i + T + 1 < n ? arr[i + T + 1] : 0);
        while(!helper.empty())
        {
            tmp2 = (helper.back() < n ? arr[helper.back()] : 0);
            if(tmp2 > tmp)
                break;
            helper.pop_back();
        }
        helper.push_back(i + T + 1);

        if(i == helper.front())
            helper.pop_front();

        res += ((long long)work[i] * S);

        tmp = (helper.front() < n ? arr[helper.front()] : 0);

        work[i + 1] = work[i];
        if(work[i + 1] > tmp)
        {
            res += ((long long)(work[i] - tmp) * D);
            work[i + 1] = tmp;
        }
    }

    cout << res << '\n';
    for(i = 0; i < n; i++)
        cout << work[i] << ' ';
    return 0;
}
