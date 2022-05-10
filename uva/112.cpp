#include <cstdio>
#include <queue>
#include <cstring>
#include <map>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

struct fastio
{
    int ch;

    void init()
    {
        ch = getchar();
    }

    bool readI(int &ival)
    {
        bool negative = 0;
        do
        {
            if (ch == EOF) {
                return 0;
            }
            if (ch == '-')
            {
                negative = 1;
                ch = getchar();
                break;
            }
            else if (ch >= '0' && ch <= '9')
            {
                break;
            }
            ch = getchar();
        } while (1);

        ival = 0;
        do
        {
            ival = 10 * ival + ch - '0';
            ch = getchar();
        } while (ch >= '0' && ch <= '9');

        if (negative)
        {
            ival = -ival;
        }
        return 1;
    }

} io;

int I;
bool found;

int cal(int s) {
    while (io.ch != '(') {
        io.ch = getchar();
    }
    io.ch = getchar();
    while (io.ch <= 32) {
        io.ch = getchar();
    }

    if (io.ch == ')') {
        io.ch = getchar();
        return 1;
    }

    int u, v;
    io.readI(u);
    u += s;
    v = cal(u) + cal(u);
    if (v == 2 && u == I) {
        found = 1;
    }

    while (io.ch != ')') {
        io.ch = getchar();
    }
    io.ch = getchar();

    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    io.init();
    while (io.readI(I)) {
        found = 0;
        cal(0);
        puts(found ? "yes" : "no");
    }
    return 0;
}
