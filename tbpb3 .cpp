#include <iostream>
#include <cstdio>
#include <cstring>

const long long modulo = 1e9 + 7;
long long f[10000][3][2];
std::string a;

long long dp(int index, short s, bool ch)
{
    if(index == a.size())
        return ((s == 0) && (!ch));
    if(f[index][s][ch] != -1)return f[index][s][ch];

    f[index][s][ch] = 0;
    if(ch)
    {
        for(int i = 0; i < a[index]; ++i)
            if(i % 3 == 0)
                f[index][s][ch] = (f[index][s][ch] + dp(index + 1, s, false))%modulo;
            else f[index][s][ch] = (f[index][s][ch] + dp(index + 1, (s + 1)% 3, false))%modulo;

        if(a[index] % 3 == 0)
            f[index][s][ch] = (f[index][s][ch] + dp(index + 1, s, true))%modulo;
        else f[index][s][ch] = (f[index][s][ch] + dp(index + 1, (s + 1)% 3, true))%modulo;
    }
    else
    {
        for(int i = 0; i <= 9; ++i)
            if(i % 3 == 0)
                f[index][s][ch] = (f[index][s][ch] + dp(index + 1, s, false))%modulo;
            else f[index][s][ch] = (f[index][s][ch] + dp(index + 1, (s + 1)% 3, false))%modulo;
    }
    return f[index][s][ch];
}
///351224178
///333340109684604927
int main()
{
    freopen("tbpb3.inp", "r", stdin);
    freopen("tbpb3.out", "w", stdout);

    std::cin >> a;

    memset(f, 0xFF, sizeof(f));
    for(int i = 0; i < a.size(); ++i)
        a[i] = a[i] - '0';

    std::cout << dp(0, 0, true);
    return 0;
}
