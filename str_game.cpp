#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

string a, b, str;
stack<int> pos[26];

int it, vt;
bool turn;
int main()
{
    freopen("str_game.inp", "r", stdin);
    freopen("str_game.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(); cout.tie(0);

    cin >> str;
    a = b = "";

    for(int i = 0; i < str.size(); ++i)
        pos[str[i] - 'a'].push(i);

    turn = false;
    it = str.size() - 1;
    vt = 0;

    for(int i = str.size(); i > 0; --i)
    {
        if(!turn)
        {
            while(it > 0)
            {
                if(str[it] != ' ')
                    break;
                it--;
            }

            a += str[it];
            pos[str[it] - 'a'].pop();
            str[it] = ' ';

            turn = true;
        }
        else
        {
            while(pos[vt].empty())
                vt++;

            b += char(vt + 'a');
            str[pos[vt].top()] = ' ';
            pos[vt].pop();

            turn = false;
        }
    }

    if(b < a)
        cout << b;
    else cout << 0;
    return 0;
}
