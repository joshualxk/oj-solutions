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

int N, K, arr[77];
bool used[2][77][6][3];
int dp[2][77][6][3];
int ix;
int ix2;

#define LR 0
#define L 1
#define R 2

void cal()
{
    ix2 = ix;
    ix ^= 1;
    int i, j, j2, m, n, u, v;
    memset(dp[ix], -1, sizeof(dp[0]));
    memset(used[ix], 0, sizeof(used[0]));
    for (i = 1; i <= N; ++i)
    {
        if (arr[i] >= 0)
        {
            j = 0;
            j2 = 0;
        }
        else
        {
            j = 1;
            j2 = 0;
        }
        for (; j <= K; ++j, ++j2)
        {
            u = -1;
            for (m = 0; m < 3; ++m)
            {
                if (used[ix2][i][j2][m] && (u < 0 || dp[ix2][i][j2][m] > dp[ix2][i][j2][u]))
                {
                    u = m;
                }
            }
            if (u >= 0)
            {
                v = dp[ix2][i][j2][u] + arr[i];
                used[ix][i][j][LR] = 1;
                dp[ix][i][j][LR] = v;
                used[ix][i][j][L] = 1;
                dp[ix][i][j][L] = v;
                used[ix][i][j][R] = 1;
                dp[ix][i][j][R] = v;
            }

            if (used[ix][i - 1][j2][R])
            {
                if (!used[ix][i][j][R])
                {
                    used[ix][i][j][R] = 1;
                    dp[ix][i][j][R] = dp[ix][i - 1][j2][R] + arr[i];
                }
                else
                {
                    dp[ix][i][j][R] = max(dp[ix][i][j][R], dp[ix][i - 1][j2][R] + arr[i]);
                }
            }
        }
    }

    for (i = N; i >= 1; --i)
    {
        if (arr[i] >= 0)
        {
            j = 0;
            j2 = 0;
        }
        else
        {
            j = 1;
            j2 = 0;
        }

        for (; j <= K; ++j, ++j2)
        {
            if (used[ix][i + 1][j2][L])
            {
                if (!used[ix][i][j][L])
                {
                    used[ix][i][j][L] = 1;
                    dp[ix][i][j][L] = dp[ix][i + 1][j2][L] + arr[i];
                }
                else
                {
                    dp[ix][i][j][L] = max(dp[ix][i][j][L], dp[ix][i + 1][j2][L] + arr[i]);
                }
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int kase, i, j;
    int ans;
    bool flag;
    io.init();
    for (kase = 1;; ++kase)
    {
        io.readI(N);
        io.readI(K);
        if (!N && !K)
        {
            break;
        }

        ix = 0;

        memset(used, 0, sizeof(used));
        used[0][1][0][LR] = 1;
        dp[0][1][0][LR] = 0;
        for (i = 1; i <= N; ++i)
        {
            for (j = 1; j <= N; ++j)
            {
                io.readI(arr[j]);
            }
            cal();
        }

        flag = 0;

        for (i = 0; i <= K; ++i)
        {
            for (j = 0; j < 3; ++j)
            {
                if (used[ix][N][i][j])
                {
                    if (!flag)
                    {
                        flag = 1;
                        ans = dp[ix][N][i][j];
                    }
                    else if (dp[ix][N][i][j] > ans)
                    {
                        ans = dp[ix][N][i][j];
                    }
                }
            }
        }

        printf("Case %d: ", kase);
        if (flag)
        {
            printf("%d\n", ans);
        }
        else
        {
            puts("impossible");
        }
    }
    return 0;
}
