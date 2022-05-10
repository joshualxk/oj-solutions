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

    int readStr(char *str)
    {
        while (ch == '\n' || ch == ' ')
        {
            ch = getchar();
        }

        int i;
        for (i = 0; ch != ' ' && ch != '\n' && ch != EOF; ++i)
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

int N, M;
int letterMap[256];
char letters[16];
int orders[16];
bool edges[15][15];

int dp[1 << 19];

char ans[16];

int cmp2(int a, int b) {
    return letters[a] < letters[b];
}

bool cal()
{
    queue<int> q;
    int i, j, st, cur, mask, u, v, ed;
    memset(dp, 0, sizeof(dp));
    dp[1 << 4] = 1 << 4;

    ed = (((1 << N) - 1) << 4) | (N - 1);

    q.push(1<<4);
    while (!q.empty())
    {
        st = q.front();
        q.pop();

        cur = st & 0xf;
        mask = st >> 4;

        for (i = 1; i < N - 1; ++i)
        {
            j = orders[i];
            if (edges[cur][j] && (mask & (1 << j)) == 0)
            {
                u = ((mask | (1 << j)) << 4) | j;
                if (!dp[u])
                {
                    dp[u] = st;
                    q.push(u);
                }
            }
        }

        if (edges[cur][N - 1] && (mask & (1 << (N - 1))) == 0)
        {
            u = ((mask | (1 << (N - 1))) << 4) | (N - 1);
            if (u == ed)
            {
                dp[u] = st;
                break;
            }
        }
    }

    if (dp[ed]) {
        u = ed;
        for (i = N - 1; i > 0; --i) {
            j = u & 0xf;
            ans[i] = letters[j];
            u = dp[u];
        }
        ans[N] = 0;
        ans[0] = letters[0];
        return 1;
    }
    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, kase, i, u, v;
    char str[8], str2[8];
    io.init();
    io.readI(T);
    for (kase = 1; kase <= T; ++kase)
    {
        io.readI(N);
        io.readI(M);

        for (i = 0; i < N; ++i)
        {
            orders[i] = i;
            io.readStr(str);
            letterMap[str[0]] = i;
            letters[i] = str[0];
        }
        memset(edges, 0, sizeof(edges));
        for (i = 0; i < M; ++i)
        {
            io.readStr(str);
            io.readStr(str2);

            u = letterMap[str[0]];
            v = letterMap[str2[0]];

            edges[u][v] = 1;
            edges[v][u] = 1;

        }

        sort(orders + 1, orders + N - 1, cmp2);

        if (cal()) {
            printf("Case %d: %s\n", kase, ans);
        } else {
            printf("Case %d: impossible\n", kase);
        }
    }
    return 0;
}
