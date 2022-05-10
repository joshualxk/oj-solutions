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

    int readStr(char *str)
    {
        ch = getchar();
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

} io;

char str[90];
int L;

int dp[90][90];
int cnts[101];

void cal()
{
    int i, j, k, u;
    memset(dp, 0x3f, sizeof(dp));

    for (i = 0; i < L; ++i)
    {
        dp[i][i] = 1;
    }

    for (i = 1; i <= L >> 1; ++i)
    {
        memset(cnts, 0, sizeof(cnts));
        for (j = i; j < L; ++j)
        {
            if (str[j] == str[j - i])
            {
                if (j == i)
                {
                    cnts[j] = 1;
                }
                else
                {
                    cnts[j] = cnts[j - 1] + 1;
                }
            }
        }
        for (j = 0; j < L - i; ++j)
        {
            if (dp[j][j + i - 1] > 1000)
            {
                for (k = j; k < j + i - 1; ++k)
                {
                    if (dp[j][j + i - 1] > dp[j][k] + dp[k + 1][j + i - 1])
                    {
                        dp[j][j + i - 1] = dp[j][k] + dp[k + 1][j + i - 1];
                    }
                }
            }
            for (k = 1; cnts[j + k * i + i - 1] - cnts[j + k * i - 1] >= i; ++k)
            {
                if (dp[j][j + k * i + i - 1] > dp[j][j + i - 1])
                {
                    dp[j][j + k * i + i - 1] = dp[j][j + i - 1];
                }
            }
        }
    }

    for (i = 1; i < L; ++i)
    {
        for (j = 0; j < L - i; ++j)
        {
            for (k = j; k < j + i; ++k)
            {
                if (dp[j][j + i] > dp[j][k] + dp[k + 1][j + i])
                {
                    dp[j][j + i] = dp[j][k] + dp[k + 1][j + i];
                }
            }
        }
    }
    printf("%d\n", dp[0][L - 1]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while (1)
    {
        L = io.readStr(str);
        if (str[0] == '*')
        {
            break;
        }
        cal();
    }
    return 0;
}
