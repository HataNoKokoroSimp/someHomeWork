#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <stack>

using namespace std;

///chuyen sang bieu thuc hau to va tinh

string str;
long long num;

stack<pair<long long, long long> > res;
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

pair<long long, long long> tmpCal;
void cal(const char &op)
{
    tmpCal = res.top(); res.pop();
    ///cout << res.top() << op << tmpCal << '\n';
    if(op == '+')
    {
        tmpCal.first = res.top().first + tmpCal.first;
        tmpCal.second = res.top().second + tmpCal.second;
    }
    else if(op == '-')
    {
        tmpCal.first = res.top().first - tmpCal.first;
        tmpCal.second = res.top().second - tmpCal.second;
    }
    else if(op == '*')
    {
        tmpCal.first = res.top().first * tmpCal.second + tmpCal.first * res.top().second;
        tmpCal.second = res.top().second * tmpCal.second;
    }
    else if(op == '/')
    {
        tmpCal.first = res.top().first / tmpCal.second;
        tmpCal.second = res.top().second / tmpCal.second;
    }

    res.pop();
    res.push(tmpCal);
}

bool isNum;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
            res.push(make_pair(0, num));
            isNum = false;
            num = 0;
        }

        if(str[i] == 'x')
        {
            res.push(make_pair(1, 0));
            continue;
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

    for(int i = 0; i < n; ++i)
    {
        cin >>
    }

    return 0;
}
