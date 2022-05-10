#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

bool readInt(int &num)
{
    int u = getchar();
    bool negative = 0;
    do
    {
        if (u == EOF)
        {
            return 0;
        }
        if (u == '-')
        {
            negative = 1;
            u = getchar();
            break;
        }
        else if (u >= '0' && u <= '9')
        {
            break;
        }
        u = getchar();
    } while (1);

    num = u - '0';
    u = getchar();
    while (u >= '0' && u <= '9')
    {
        num = num * 10 + u - '0';
        u = getchar();
    }
    if (negative) {
        num = -num;
    }
    return 1;
}

#define MAXN 729
#define YES 1
#define NO 2
#define UNKNOWN 3
int dp[MAXN + 1];

int calS(int val) {
    int ret = 0, u;
    while (val) {
        u = val % 10;
        ret += u * u;
        val /= 10;
    }
    return ret;
}

void init() {
    int arr[MAXN + 1];
    int ix, i, j, u;
    dp[1] = YES;
    for (i = 2; i <= MAXN; ++i) {
        if (dp[i]) {
            continue;
        }
        j = i;
        ix = 0;
        while (!dp[j]) {
            dp[j] = UNKNOWN;
            arr[ix++] = j;
            j = calS(j);
        }
        u = dp[j] == UNKNOWN ? NO : dp[j];
        for (j = 0; j < ix; ++j) {
            dp[arr[j]] = u;
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
    init();
    int T, N, u;
    readInt(T);
    for (int i = 1; i <= T; ++i) {
        readInt(N);
        u = N;
        if (u > MAXN) {
            u = calS(u); 
        }
        printf("Case #%d: %d is a%s number.\n", i, N, dp[u] & YES ? " Happy" : "n Unhappy");
    }
    return 0;
}
