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
        for (i = 0; ch != ' ' && ch != '\n'; ++i)
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

int N;
int heads[10005];
int ns[20005];
int vs[20005];
int ix;

int dis[10005];
int qu[10005];
int cal()
{
    int i, u, v;
    int head = 0, tail = 1;
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    qu[0] = 1;
    while (head != tail)
    {
        u = qu[head++];

        for (i = heads[u]; i; i = ns[i])
        {
            v = vs[i];
            if (dis[v] > 1 << 15)
            {
                dis[v] = dis[u] + 1;
                qu[tail++] = v;
            }
        }
    }

    memset(dis, 0x3f, sizeof(dis));
    qu[0] = u;
    head = 0;
    tail = 1;
    dis[u] = 0;
    while (head != tail)
    {
        u = qu[head++];

        for (i = heads[u]; i; i = ns[i])
        {
            v = vs[i];
            if (dis[v] > 1 << 15)
            {
                dis[v] = dis[u] + 1;
                qu[tail++] = v;
            }
        }
    }

    return dis[u];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, m, i, j, u;
    io.init();
    io.readI(T);
    while (T--)
    {
        memset(heads, 0, sizeof(heads));
        ix = 0;
        io.readI(N);
        for (i = 1; i <= N; ++i)
        {
            io.readI(m);
            for (j = 1; j <= m; ++j)
            {
                io.readI(u);

                ++ix;
                vs[ix] = u;
                ns[ix] = heads[i];
                heads[i] = ix;
            }
        }

        printf("%d\n", ((N - 1) << 1) - cal());
    }
    return 0;
}
