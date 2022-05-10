
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

int joseph(int N, int K) {
    int m = 0;
    for (int i = 2; i <= N; ++i) {
        m = (m + K) % i;
    }
    return m + 2;
}

int dp[] = {1,18,10,11,7,17,11,15,29,5,21,13,26,14,11,23,22,9,73,17,42,7,98,15,61,22,84,24,30,9,38,15,54,27,9,61,38,22,19,178,38,53,79,68,166,20,9,22,7,21,72,133,41,10,82,92,64,129,86,73,67,19,66,115,52,24,22,176,10,57,137,239,41,70,60,116,81,79,55,102,49,5,22,54,52,113,15,};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    io.init();
    // int i, j;
    // for (i = 13; i < 100; ++i) {
    //     for (j = 1; ;++j) {
    //         if (joseph(i - 1, j) == 13) {
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
        printf("%d\n", dp[u - 13]);
    }
    return 0;
}
