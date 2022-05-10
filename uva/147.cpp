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

    int readStr(char *str, int &ival)
    {
        while (ch <= 32)
        {
            ch = getchar();
        }

        int i;
        ival = 0;
        for (i = 0; ch > 32; ++i)
        {
            if (ch >= '0') {
                ival = ival * 10 + ch - '0';
            }
            str[i] = ch;
            ch = getchar();
        }
        str[i] = 0;

        return i;
    }

} io;

int currencies[] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
int sz = 11;
int64_t dp[40001];

void init() {
    int i, j;
    dp[0] = 1;
    for (i = 0; i < sz; ++i) {
        for (j = 0; j < 30000; j += 5) {
            dp[j + currencies[i]] += dp[j];
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    io.init();
    init();
    char str[32];
    int u;
    while (1) {
        io.readStr(str, u);
        if (!u) {
            break;
        }
        printf("%6s%17lld\n", str, dp[u]);
    }
    return 0;
}
