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

        while (ch == ' ') {
            ch = getchar();
        }

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

#define MAXN 128
int dp[2][MAXN];
int N, M;

bool blocked[MAXN][MAXN];

int cal() {
    memset(dp , 0, sizeof(dp[0]));
    int ix = 0, i, j;
    dp[0][1] = 1;
    for (i = 1; i <= N; ++i) {
        ix ^= 1;
        for (j = 1; j <= M; ++j) {
            if (blocked[i][j]) {
                dp[ix][j] = 0;
            } else {
                dp[ix][j] = dp[ix ^ 1][j] + dp[ix][j - 1];
            }
        }
    }
    return dp[ix][M];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, kase, i, u, v;
    io.init();
    io.readI(T);
    for (kase = 0; kase < T; ++kase) {
        
        memset(blocked, 0, sizeof(blocked));
        io.readI(N);
        io.readI(M);
        for (i = 0; i < N; ++i) {
            io.readI(u);

            while (io.ch != '\n' && io.ch != EOF) {
                io.readI(v);
                blocked[u][v] = 1;
            }
        }

        if (kase) {
            putchar('\n');
        }
        printf("%d\n", cal());
    }
    return 0;
}
