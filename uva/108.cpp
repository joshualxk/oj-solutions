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
        bool negative = 0;
        do
        {
            if (ch == EOF)
            {
                return 0;
            }
            if (ch == '-')
            {
                negative = 1;
                ch = getchar();
                break;
            }
            else if (ch >= '0')
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

        if (negative)
        {
            ival = -ival;
        }
        return 1;
    }

} io;

int N;
int dp[2][101][101];
int svm[101];
int ix, ix2;
int ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, k, u;
    io.init();
    while (io.readI(N))
    {
        ix = 1;
        ans = -10000000;
        memset(dp[ix], -1, sizeof(dp[0]));
        for (i = 1; i <= N; ++i)
        {
            ix2 = ix;
            ix ^= 1;
            for (j = 1; j <= N; ++j)
            {
                io.readI(u);
                svm[j] = svm[j - 1] + u;

                for (k = j; k >= 1; --k)
                {
                    if (dp[ix2][k][j] > 0)
                    {
                        dp[ix][k][j] = dp[ix2][k][j] + svm[j] - svm[k - 1];
                    }
                    else
                    {
                        dp[ix][k][j] = svm[j] - svm[k - 1];
                    }
                    if (ans < dp[ix][k][j])
                    {
                        ans = dp[ix][k][j];
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
