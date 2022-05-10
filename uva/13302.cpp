#include <cstdio>
#include <cctype>
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

int L, N, D;

int gcd(int a, int b)
{
    int u;
    while (b)
    {
        u = a % b;
        a = b;
        b = u;
    }
    return a;
}

int gcd2(long long a, long long b)
{
    long long u;
    while (b)
    {
        u = a % b;
        a = b;
        b = u;
    }
    return (int)a;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, u, v, d1v, m0d, mak;
    long long ll;

    while (1)
    {
        readInt(L);
        readInt(N);
        readInt(D);
        if (!L)
        {
            break;
        }
        u = gcd(L, D);
        v = L / u;
        if (N >= v) {
            d1v = v;
        } else {
            m0d = v = D % L;
            mak = m0d;
            d1v = 1;
            for (i = 2; i <= N; ++i) {
                v += m0d;
                if (v >= L) {
                    v -= L;
                }
                if (v > mak) {
                    mak = v;
                    d1v = i;
                }
            }
        }
        ll = d1v;
        ll = (ll * D + L - 1) / L * L;
        u = gcd2(ll, d1v);
        ll /= u;
        d1v /= u;
        printf("%lld/%d\n", ll, d1v);
    }
    return 0;
}
