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

bool readLong(long long &num)
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
    if (negative)
    {
        num = -num;
    }
    return 1;
}

int N, H[110];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
    int i, kase = 0, avg, ans;
    while (1) {
        readInt(N);
        if (!N) {
            break;
        }
        ans = avg = 0;
        for (i = 0; i < N; ++i) {
            readInt(H[i]);
            avg += H[i];
        }
        avg /= N;
        for (i = 0; i < N; ++i) {
            if (H[i] > avg) {
                ans += H[i] - avg;
            }
        }
        printf("Set #%d\n", ++kase);
        printf("The minimum number of moves is %d.\n\n", ans);
    }
    return 0;
}
