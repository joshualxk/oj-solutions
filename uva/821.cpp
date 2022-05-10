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

int dis[101][101];
#define INFI (1 << 20)

int idxVal;
int used[101];

int tot;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int kase, i, j, k, u, v, w;
    io.init();
    for (kase = 1;; ++kase)
    {
        memset(dis, 0x1f, sizeof(dis));
        memset(used, 0, sizeof(used));
        idxVal = 0;

        for (i = 0;; ++i)
        {
            io.readI(u);
            io.readI(v);

            if (!u && !v)
            {
                if (!i)
                {
                    return 0;
                }
                break;
            }

            if (!used[u])
            {
                used[u] = ++idxVal;
            }
            u = used[u];

            if (!used[v])
            {
                used[v] = ++idxVal;
            }
            v = used[v];

            dis[u][v] = 1;
        }

        for (i = 1; i <= idxVal; ++i)
        {
            for (j = 1; j <= idxVal; ++j)
            {
                if (dis[j][i] > INFI)
                {
                    continue;
                }

                for (k = 1; k <= idxVal; ++k)
                {
                    if (dis[i][k] > INFI)
                    {
                        continue;
                    }
                    if (dis[j][k] > dis[j][i] + dis[i][k])
                    {
                        dis[j][k] = dis[j][i] + dis[i][k];
                    }
                }
            }
        }

        tot = 0;
        for (i = 1; i <= idxVal; ++i)
        {
            for (j = 1; j <= idxVal; ++j)
            {
                if (i == j)
                {
                    continue;
                }
                tot += dis[i][j];
            }
        }

        double dd = tot;
        dd /= (idxVal - 1) * idxVal;

        printf("Case %d: average length between pages = %.3lf clicks\n", kase, dd);
    }
    return 0;
}