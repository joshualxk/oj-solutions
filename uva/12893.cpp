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
    if (negative)
    {
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

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, ans;
    long long N;
    readInt(T);
    while (T--)
    {
        readLong(N);
        ans = 0;
        for (; N; N >>= 1)
        {
            ans += N & 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
