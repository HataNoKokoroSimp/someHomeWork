#include <iostream>
#include <cstdio>

///This solution may be wrong

long long A, B, N, M;
long long s;
int main()
{
    freopen("NEMCHUAP.INP", "r", stdin);
    freopen("NEMCHUAP.OUT", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> A >> B >> N >> M;

    s = std::min(A * M, B * (M + 1LL)); /// Buy M + 1 'nem chua's
    std::cout << (N/(M+1LL))*s + (N%(M + 1LL))*std::min(A, B);
    return 0;
}
/// Fumo coder
