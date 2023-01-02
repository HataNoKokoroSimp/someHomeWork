#include <iostream>
#include <cstdio>


long long sum;
void c1(long long n)
{
    sum = 0;
    for(long long i = 1; i <= n; ++i)
        sum = sum + (n % i);
    std::cout << sum << '\n';
}

/// a: start
/// b: step
/// c: amount
long long cal(long long a, long long b, long long c)
{
    if(c <= 0)return 0;
    return ( ( ((a<<1) + b*(c - 1)) * c) >> 1);
}

long long tmp, index, l, r;
void c2(long long n)
{
    sum = 0;

    index = 2;
    r = l = n;
    while(index <= l)
    {
        l = std::max(n/index, index);
        sum = sum + cal(n - r*(index - 1), index - 1, r - l);
        sum = sum + n%index;
        r = l;
        index++;
    }
    std::cout << sum;
}

long long N;
int main()
{

    std::cin >> N;
    ///c1(N);
    c2(N);
    return 0;
}
