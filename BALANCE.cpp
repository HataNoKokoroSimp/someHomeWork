#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <climits>
#include <cmath>

#define PI 3.14159265359
#define Euler 2.71828182845

#define XAMVCL touhouMode
#ifdef XAMVCL
    #define PatchouliKnowledge std::cin
    #define ShameimaruAya std::cout
    typedef int HakureiReimu;
    typedef unsigned int KirisameMarisa;
    typedef short Daiyousei;
    typedef unsigned short Cirno9;
    typedef long long IbukiSuika;
    typedef unsigned long long YakumoYukari;
    typedef bool YakumoRan;
    typedef char Chen;
    typedef std::string HataNoKokoro;
    #define KijinSeija(It1, It2) std::reverse(It1, It2)
    #define IzayoiSakuya1(It1, It2) std::sort(It1, It2)
    #define IzayoiSakuya2(It1, It2, comp) std::sort(It1, It2, comp)
    #define HouraisanKaguya while
    #define Rumia for
    #define AliceMargatroid if
    #define AliceDoll else
    #define HecatiaLapislazuli std::vector
    #define KazamiYuuka std::pair
    #define Junko(num) std::abs(num)
#endif // XAMVCL

typedef long long ll;
typedef unsigned long long ull;

template<typename _T>
void selfSwap(_T &a, _T &b)
{
    _T c = a;
    a = b;
    b = c;
}

template<typename _T>
void display(_T *st, size_t si, bool isDown)
{
    for(_T *i = st; i != st + si; i++)
        std::cout << *i << (isDown ? '\n' : ' ');
    std::cout << '\n';
}

template<typename _T1, typename _T2>
_T1 qPow(_T1 a, ll b, _T2 modulo)
{
    _T1 res = 1;
    while(b > 0)
    {
        if(b&1)res = res*a%modulo;
        a = a*a%modulo;
        b = (b >> 1);
    }
    return res;
}

template<typename _T1, typename _T2>
_T1 qPow(_T1 a, _T1 startValue, ll b, _T2 modulo)
{
    _T1 res = startValue;
    while(b > 0)
    {
        if(b&1)res = res*a%modulo;
        a = a*a%modulo;
        b = (b >> 1);
    }
    return res;
}

template<typename _T1>
_T1 qPow(_T1 a, int b)
{
    _T1 res = 1;
    while(b > 0)
    {
        if(b&1)res = res*a;
        a = a*a;
        b = (b >> 1);
    }
    return res;
}

std::pair<ll, ll> LinearDioEq(ll a, ll b)
{
    ll temp;
    ll xA = 1, xB = 0;
    ll q;
    while(b != 0)
    {
        q = a/b;
        temp = a - q*b; a = b; b = temp;
        temp = xA - q*xB; xA = xB; xB = temp;
    }
    return std::make_pair(xA, a);
}

ll Dio_inverse(ll n, ll modulo)
{
    return LinearDioEq(n, modulo).first;
}

ll SmallFermat_inverse(ll n, ll modulo)
{
    return qPow(n, modulo - 2, modulo);
}

std::string NumToString(ll num)
{
    if(num == 0)return "0";
    std::string tempString = "";
    if(num < 0)
    {
        tempString = tempString + '-';
        num = -num;
    }

    while(num > 0)
    {
        tempString = char(num%10 + '0') + tempString;
        num/=10;
    }
    return tempString;
}

namespace binIndexTree
{
    template<typename _T>
    void add(_T* st, size_t si, _T value, size_t index)
    {
        index++;
        while(index <= si)
        {
            *(st + index - 1) = *(st + index - 1) + value;
            index = index + (index&(-index));
        }
    }

    template<typename _T, typename _T_res>
    _T_res getSum(_T* st, size_t index)
    {
        _T_res result = 0;
        index++;
        while(index > 0)
        {
           result = result + *(st + index - 1);
           index = index - (index&(-index));
        }
        return result;
    }

    template<typename _T, typename _T_res>
    _T_res getSumEx(_T* st, size_t l, size_t r)
    {
        return getSum<_T, _T_res>(st, r) - getSum<_T, _T_res>(st, l - 1);
    }
}

#define CREATE_TES
void createTest()
{
    std::cout << "100\n";
    srand(time(NULL));
    for(int i = 1; i <= 100; ++i)
    {
        std::cout << rand() << ' ' << rand() << '\n';
        if(rand() % 10 == 0)
            srand(rand() + time(NULL));
    }
}

/*struct segmentTree
{
    int value, lPos, rPos;
    segmentTree *left;
    segmentTree *right;

    segmentTree()
    {
        value = 0;
        left = right = NULL;
    }

    void setVal(const int &index, const int &val)
    {
        if(index < this->lPos || index > rPos)return;
        if(lPos == rPos)
        {
            this->value = val;
            return;
        }

        this->value = 0;
        if(left != NULL)
        {
            left->setVal(index, val);
            this->value = left->value;
        }

        if(right != NULL)
        {
            right->setVal(index, val);
            this->value = this->value + right->value;
        }
    }

    void divideSegment(int mid)
    {
        left = new segmentTree();
        left->lPos = this->lPos;
        left->rPos = mid;

        right = new segmentTree();
        right->lPos = mid + 1;
        right->rPos = this->rPos;
    }

    void createTree()
    {
        if(lPos < rPos)
        {
            divideSegment((lPos + rPos) >> 1);
            left->createTree();
            right->createTree();
        }
    }

    void deleteTree()
    {
        if(left != NULL)left->deleteTree();
        if(right != NULL)right->deleteTree();
        delete this;
    }

    int getPos(const int &k)
    {
        if(lPos == rPos) return lPos;
        if(left != NULL)
        {
            if(k > left->value)
            {
                if(right != NULL) return right->getPos(k - left->value);
                return -1;
            }
            return left->getPos(k);
        }
        return -1;
    }
};*/

void presolve()
{}

HakureiReimu HongMeiling, Koakuma;
HecatiaLapislazuli<HakureiReimu> RemiliaScarlet;
HakureiReimu FujiwaraNoMokou, KonpakuYoumu, RealFumo;

void solve()
{
    PatchouliKnowledge >> FujiwaraNoMokou;
    KonpakuYoumu = RealFumo = 0;
    Rumia(HakureiReimu Fumo = 0; Fumo < FujiwaraNoMokou; Fumo++)
    {
        PatchouliKnowledge >> HongMeiling;
        RemiliaScarlet.push_back(HongMeiling);
        KonpakuYoumu = KonpakuYoumu + HongMeiling;
    }

    HongMeiling = KonpakuYoumu/FujiwaraNoMokou;
    Koakuma = KonpakuYoumu%FujiwaraNoMokou;
    IzayoiSakuya1(RemiliaScarlet.begin(), RemiliaScarlet.end());

    Rumia(HakureiReimu Fumo = 0; Fumo < FujiwaraNoMokou; Fumo++)
    {
        AliceMargatroid(FujiwaraNoMokou - Fumo > Koakuma)
            RealFumo = RealFumo + Junko(RemiliaScarlet[Fumo] - HongMeiling);
        AliceDoll
            RealFumo = RealFumo + Junko(RemiliaScarlet[Fumo] - (HongMeiling + 1));
    }
    ShameimaruAya << (RealFumo >> 1);
}

#define QUICK_IO
int T;
int main()
{
    #ifdef CREATE_TEST
        freopen("input.txt", "w", stdout);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);std::cout.tie(NULL);
        createTest();
        return 0;
    #endif

    freopen("BALANCE.INP", "r", stdin);
    freopen("BALANCE.OUT", "w", stdout);

    #ifdef QUICK_IO
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);
    #endif // QUICK_IO

    presolve();
    #ifdef MULTI_TEST
        std::cin >> T;
        while(T)
        {
            solve();
            T--;
        }
    #else
        solve();
    #endif // MULTI_TEST
    return 0;
}
