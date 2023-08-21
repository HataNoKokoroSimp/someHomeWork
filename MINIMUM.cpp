#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

const int maxN = 5e5;

int n, k;
int arr[maxN];

deque<int> helper;

int main()
{
    freopen("MINIMUM.INP", "r", stdin);
    freopen("MINIMUM.OUT", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;

    int i;
    for(i = 0; i < n; i++)
        cin >> arr[i];

    for(i = 0; i < k - 1; i++)
    {
        while(!helper.empty())
        {
            if(arr[helper.back()] < arr[i])
                break;
            helper.pop_back();
        }

        helper.push_back(i);
    }

    for(i = k - 1; i < n; i++)
    {
        while(!helper.empty())
        {
            if(arr[helper.back()] < arr[i])
                break;
            helper.pop_back();
        }
        helper.push_back(i);

        cout << arr[helper.front()] << '\n';

        if(helper.front() == i - k + 1)
            helper.pop_front();
    }

    return 0;
}
