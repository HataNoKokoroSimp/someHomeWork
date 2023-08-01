#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <stack>

using namespace std;

///chuyen sang bieu thuc hau to va tinh

string str;
long long num;

stack<long double> res;
stack<char> oper;

short prio(const char &a)
{
    switch(a)
    {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 3;
    }
    return 4;
}

long double tmpCal;
void cal(const char &op)
{
    tmpCal = res.top(); res.pop();
    ///cout << res.top() << op << tmpCal << '\n';
    if(op == '+')
        tmpCal = res.top() + tmpCal;
    else if(op == '-')
        tmpCal = res.top() - tmpCal;
    else if(op == '*')
        tmpCal = res.top() * tmpCal;
    else if(op == '/')
        tmpCal = res.top() / tmpCal;

    res.pop();
    res.push(tmpCal);
}

bool isNum;
int main()
{
    freopen("Bieuthuc.inp", "r", stdin);
    freopen("Bieuthuc.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    getline(cin, str);
    str += ')';
    oper.push('(');

    isNum = false;
    for(int i = 0; i < str.size(); ++i)
    {
        if('0' <= str[i] && str[i] <= '9')
        {
            num = num * 10 + (str[i] - '0');
            isNum = true;
            continue;
        }

        if(isNum)
        {
            res.push(num);
            isNum = false;
            num = 0;
        }

        if(str[i] == ' ')
            continue;

        if(str[i] == '(')
        {
            oper.push('(');
            continue;
        }

        if(str[i] == ')')
        {
            while(oper.top() != '(')
            {
                cal(oper.top());
                oper.pop();
            }oper.pop();

            continue;
        }

        while(prio(str[i]) <= prio(oper.top()))
        {
            cal(oper.top());
            oper.pop();
        }
        oper.push(str[i]);
    }

    cout << fixed << setprecision(6) << res.top();

    return 0;
}
