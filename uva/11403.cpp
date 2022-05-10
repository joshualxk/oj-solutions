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

    int readStr(char *str, int64_t &lval)
    {
        while (ch <= 32)
        {
            ch = getchar();
        }

        int i;
        lval = 0;
        for (i = 0; ch > 32; ++i)
        {
            str[i] = ch;
            lval = (lval << 1) + (ch == '1');
            ch = getchar();
        }
        str[i] = 0;

        return i;
    }

} io;

char A[32], B[32], C[64], D[64], E[64], F[64];
int la, lb, lc;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int kase, i, j, w, w2;
    int64_t a, b;
    io.init();
    memset(D, '0', sizeof(D));
    memset(E, '-', sizeof(E));
    memset(F, ' ', sizeof(F));
    D[63] = 0;
    E[63] = 0;
    F[63] = 0;
    for (kase = 0;; ++kase)
    {

        la = io.readStr(A, a);
        lb = io.readStr(B, b);
        if (A[0] == '0' && B[0] == '0')
        {
            break;
        }

        a *= b;

        if (!a)
        {
            lc = 1;
            C[62] = '0';
        }
        else
        {
            for (i = 62; a; --i)
            {
                C[i] = (a & 1) + '0';
                a >>= 1;
            }
            lc = 62 - i;
        }

        if (kase)
        {
            putchar('\n');
        }

        w2 = max(la, lb);
        w = max(lc, w2);
        printf("%s%s\n", F + 63 - (w - la), A);
        printf("%s%s\n", F + 63 - (w - lb), B);
        printf("%s%s\n", F + 63 - (w - w2), E + 63 - w2);
        for (i = lb - 1, j = w - la; i >= 0; --i, --j)
        {
            if (B[i] == '0')
            {
                printf("%s%s\n", F + 63 - (j), D + 63 - la);
            }
            else
            {
                printf("%s%s\n", F + 63 - (j), A);
            }
        }
        puts(E + 63 - w);
        printf("%s%s\n", F + 63 - (w - lc), C + 63 - lc);
    }

    return 0;
}
