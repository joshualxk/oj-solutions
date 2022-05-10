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

bool joseph(int N, int K) {
    int m = 0;
    int i;
    for (i = 0; i < N; ++i) {
        m = (m + K - 1) % (2 * N - i);
        if (m < N) {
            return 0;
        }
    }
    return 1;
}

int dp[] = {0, 2,7,5,30,169,441,1872,7632,1740,93313,459901,1358657,2504881,};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    io.init();
    // int i, j;
    // for (i = 1; i < 14; ++i) {
    //     for (j = i + 1; ;++j) {
    //         if (joseph(i, j)) {
    //             printf("%d,", j);
    //             break;
    //         }
    //     }
    // }
    int u;
    while (1) {
        io.readI(u);
        if (!u) {
            break;
        }
        printf("%d\n", dp[u]);
    }
    return 0;
}
