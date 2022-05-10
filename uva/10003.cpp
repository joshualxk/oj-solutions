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
        do
        {
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

} io;

int L, N, cuts[52];
int dp[52][52];

int cal()
{
    int i, j, k, i2, u, m1n;
    memset(dp, 0x3f, sizeof(dp));
    for (i = 1; i <= N + 1; ++i)
    {
        dp[i - 1][i] = 0;
    }
    for (i = 2; i <= N + 1; ++i)
    {
        for (j = 0; j <= N + 1 - i; ++j)
        {
            k = j + i;
            m1n = 1 << 30;
            for (i2 = j + 1; i2 < k; ++i2)
            {
                u = dp[j][i2] + dp[i2][k];
                if (m1n > u)
                {
                    m1n = u;
                }
            }
            dp[j][k] = m1n + cuts[k] - cuts[j];
        }
    }
    return dp[0][N + 1];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i;
    io.init();
    while (1)
    {
        io.readI(L);
        if (!L)
        {
            break;
        }
        io.readI(N);
        for (i = 1; i <= N; ++i)
        {
            io.readI(cuts[i]);
        }
        cuts[0] = 0;
        cuts[N + 1] = L;

        printf("The minimum cutting is %d.\n", cal());
    }

    return 0;
}
