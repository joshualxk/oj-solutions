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
#define BUFF_SIZE (1 << 2)
    char buff[BUFF_SIZE + 64];
    int ix;

    int ch;

    void init()
    {
        ix = 0;
        ch = getchar();
    }

    bool skip()
    {
        while (ch == ' ' || ch == '\n')
        {
            ch = getchar();
        }
        return ch != EOF;
    }

    bool readI(int &ival)
    {
        do
        {
            if (ch >= '0' && ch <= '9')
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

        return 1;
    }

    int readStr(char *str)
    {
        while (ch == '\n' || ch == ' ')
        {
            ch = getchar();
        }

        int i;
        for (i = 0; ch != '\n'; ++i)
        {
            str[i] = ch - '0';
            ch = getchar();
        }
        // str[i] = 0;

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

int R, C;
char grid[1002 * 1002];

int vis[1002 * 1002];

int dxy[8];

int st, ed;

int stk[2][1<<14], stkix[2];

int cal()
{
    int d, i, j, u, v, ix = 1;
    if (st == ed)
    {
        return 0;
    }
    memset(vis + C + 2, 0x3f, sizeof(vis[0]) * ((C + 2) * R));
    j = C + 2;
    for (i = 1; i <= R; ++i)
    {
        vis[j] = 0;
        vis[j + C + 1] = 0;
        j += C + 2;
    }

    stkix[0] = stkix[1] = 0;
    vis[st] = 0;
    stk[0][stkix[0]++] = st;
    for (;;)
    {
        ix ^= 1;
        while (stkix[ix])
        {
            u = stk[ix][--stkix[ix]];

            if (u == ed)
            {
                goto _out;
            }

            d = grid[u];
            v = u + dxy[d];

            if (vis[v] > vis[u])
            {
                vis[v] = vis[u];
                stk[ix][stkix[ix]++] = v;
            }

            for (i = 0; i < 8; ++i)
            {
                if (i == d)
                {
                    continue;
                }

                v = u + dxy[i];

                if (vis[v] > vis[u] + 1)
                {
                    vis[v] = vis[u] + 1;
                    stk[ix ^ 1][stkix[ix^1]++] = v;
                }
            }
        }
    }
_out:
    return vis[ed];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, n, u, v;
    io.init();
    while (io.skip())
    {
        io.readI(R);
        io.readI(C);
        for (i = 1, j = C + 3; i <= R; ++i, j += C + 2)
        {
            io.readStr(grid + j);
        }

        dxy[0] = -(C + 2);
        dxy[1] = -(C + 1);
        dxy[2] = 1;
        dxy[3] = C + 3;
        dxy[4] = C + 2;
        dxy[5] = C + 1;
        dxy[6] = -1;
        dxy[7] = -(C + 3);

        memset(vis, 0, sizeof(vis[0]) * (C + 2));
        memset(vis + (R + 1) * (C + 2), 0, sizeof(vis[0]) * (C + 2));
        io.readI(n);
        for (i = 0; i < n; ++i)
        {
            io.readI(u);
            io.readI(v);
            st = u * (C + 2) + v;
            io.readI(u);
            io.readI(v);
            ed = u * (C + 2) + v;
            printf("%d\n", cal());
        }
    }
    return 0;
}
