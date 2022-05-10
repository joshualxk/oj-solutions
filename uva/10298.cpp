#include <cstdio>
#include <queue>
#include <cstring>
#include <map>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int cnts[128];

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
        memset(cnts, 0, sizeof(cnts));
        for (i = 0; ch > 32; ++i)
        {
            ++cnts[ch];
            str[i] = ch;
            ch = getchar();
        }
        str[i] = 0;

        return i;
    }

} io;

char str[1000010];
int F[1000010];
int L;
int ans;

int gcd(int u, int v)
{
    int tmp;
    while (v)
    {
        tmp = u % v;
        u = v;
        v = tmp;
    }
    return u;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, m;
    while (1)
    {
        L = io.readStr(str);
        if (str[0] == '.')
        {
            break;
        }
        m = L;

        ans = 1;
        for (i = 0; i < 128; ++i)
        {
            if (cnts[i] == L)
            {
                ans = L;
                goto _out;
            }
            else if (cnts[i])
            {
                m = gcd(m, cnts[i]);
                if (m == 1)
                {
                    goto _out;
                }
            }
        }

        F[0] = -1;
        for (i = 1, j = -1; i < L; ++i)
        {
            while (j >= 0 && str[i] != str[j + 1])
            {
                j = F[j];
            }
            if (str[i] == str[j + 1])
            {
                ++j;
            }
            F[i] = j;
        }

        m = L - F[L - 1] - 1;
        if (L % m == 0)
        {
            ans = L / m;
        }

    _out:
        printf("%d\n", ans);
    }
    return 0;
}
