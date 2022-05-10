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
#define BUFF_SIZE (1 << 12)
    char buff[BUFF_SIZE + 64];
    int ix;

    int ch;

    void init()
    {
        ix = 0;
        ch = getchar();
    }

    bool readI(int &ival)
    {
        bool negative = 0;
        do
        {
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

    void skip()
    {
        while (ch == '\n' || ch == ' ')
        {
            ch = getchar();
        }
    }

    int readStr(char *str)
    {
        while (ch == '\n' || ch == ' ')
        {
            ch = getchar();
        }

        int i;
        for (i = 0; ch != EOF && ch != ' ' && ch != '\n'; ++i)
        {
            str[i] = ch;
            ch = getchar();
        }
        str[i] = 0;

        return i;
    }

    void concat(const char *str, int len)
    {
        memmove(buff + ix, str, len);
        ix += len;
    }

    void i2s(int val)
    {
        static char digits[16];
        if (val < 10)
        {
            buff[ix++] = val + '0';
        }
        else
        {
            int i, u;
            for (i = 14, u = val; u; u /= 10, --i)
            {
                digits[i] = u % 10 + '0';
            }
            for (++i; i <= 14; ++i)
            {
                buff[ix++] = digits[i];
            }
        }
    }

    void flush(bool force)
    {
        if (ix >= BUFF_SIZE || (force && ix))
        {
            buff[ix] = 0;

            printf("%s", buff);
            ix = 0;
        }
    }
} io;

int P1[26], P2[26];

int getP1(int u) {
    return P1[u] == u ? u : P1[u] = getP1(P1[u]);
}

int getP2(int u) {
    return P2[u] == u ? u : P2[u] = getP2(P2[u]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, kase, n, i, u, v, w;
    char str1[8], str2[8];
    io.init();
    io.readI(T);
    for (kase = 0; kase < T; ++kase)
    {
        for (i = 0; i < 26; ++i) {
            P1[i] = P2[i] = i;
        }
        io.readI(n);
        while (n--)
        {
            io.readStr(str1);
            io.readStr(str2);

            u = str1[0] - 'A';
            v = str2[0] - 'A';
            u = getP1(u);
            v = getP1(v);
            if (u == v) {
                continue;
            }
            if (u > v) {
                w = u;
                u = v;
                v = w;
            }
            P1[v] = u;
        }

        io.readI(n);
        while (n--)
        {
            io.readStr(str1);
            io.readStr(str2);

            u = str1[0] - 'A';
            v = str2[0] - 'A';
            u = getP2(u);
            v = getP2(v);
            if (u == v) {
                continue;
            }
            if (u > v) {
                w = u;
                u = v;
                v = w;
            }
            P2[v] = u;
        }

        for (i = 0; i < 26; ++i) {
            if (getP1(i) != getP2(i)) {
                goto _out;
            }

        }

        _out:
        if (kase) {
            io.buff[io.ix++] = '\n';
        }
        if (i == 26) {
            io.buff[io.ix++] = 'Y';
            io.buff[io.ix++] = 'E';
            io.buff[io.ix++] = 'S';
        } else {
            io.buff[io.ix++] = 'N';
            io.buff[io.ix++] = 'O';
        }
        io.buff[io.ix++] = '\n';
        io.flush(0);
    }
    io.flush(1);
    return 0;
}
