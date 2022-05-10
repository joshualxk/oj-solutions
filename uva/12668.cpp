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
            if (ch == EOF)
            {
                return 0;
            }
            if (ch >= '0')
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
        } while (ch >= '0');

        return 1;
    }

    int readStr(char *str)
    {
        while (ch <= 32)
        {
            ch = getchar();
        }

        int i;
        for (i = 0; ch > 32; ++i)
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
char grid[102][102];
int rowno[102][102];
int colno[102][102];

int rowix;
int colix;

int heads[10000];
int vs[20010];
int ns[20010];
int ix;

int pr[10000];
bool vis[10000];

bool match(int u) {
    int i, v;
    for (i = heads[u];i;i=ns[i]) {
        v = vs[i];
        if (!vis[v]) {
            vis[v] = true;
            if (pr[v] < 0 || match(pr[v])) {
                pr[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int cal() {
    int i;
    int ans = 0;
    memset(pr, -1, sizeof(pr));
    for (i = 0; i < rowix; ++i) {
        memset(vis, 0, sizeof(vis));
        if (match(i)) {
            ++ans;
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j;
    io.init();
    while (io.readI(N))
    {
        rowix = 0;
        colix = 5000;
        memset(heads, 0, sizeof(heads));
        ix = 0;
        for (i = 1; i <= N; ++i)
        {
            io.readStr(grid[i] + 1);

            for (j = 1; j <= N; ++j)
            {
                if (grid[i][j] == 'X')
                {
                    continue;
                }
                if (grid[i - 1][j] != '.')
                {
                    colno[i][j] = colix++;
                }
                else
                {
                    colno[i][j] = colno[i - 1][j];
                }

                if (grid[i][j - 1] != '.')
                {
                    rowno[i][j] = rowix++;
                }
                else
                {
                    rowno[i][j] = rowno[i][j - 1];
                }

                ++ix;
                vs[ix] = colno[i][j];
                ns[ix] = heads[rowno[i][j]];
                heads[rowno[i][j]] = ix;

                ++ix;
                vs[ix] = rowno[i][j];
                ns[ix] = heads[colno[i][j]];
                heads[colno[i][j]] = ix;
            }
        }
        printf("%d\n", cal());
    }
    return 0;
}
