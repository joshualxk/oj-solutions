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

    void init()
    {
        ch = getchar();
    }

    int readStr(char *str)
    {
        ch = getchar();

        int i;
        for (i = 0; ch > '\n'; ++i)
        {
            str[i] = ch;
            ch = getchar();
        }
        str[i] = 0;

        return i;
    }

} io;

char str[][20] = {
    "Yes",
    "Output Format Error",
    "Wrong Answer",
};

int la, lb;
char A[32], B[32];
int ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, kase, i, j;
    io.init();
    io.readI(T);
    for (kase = 1; kase <= T; ++kase)
    {
        la = io.readStr(A);
        lb = io.readStr(B);

        // printf("(%s) (%s)\n", A, B);

        ans = 0;
        for (i = 0, j = 0; A[i] && B[j]; ++i)
        {
            if (A[i] == B[j])
            {
                ++j;
                continue;
            }

            if (A[i] == ' ')
            {
                ans = 1;
                continue;
            }
            break;
        }
        if (A[i] == ' ')
        {
            ans = 1;
            for (; A[i] == ' '; ++i)
                ;
        }

        if (A[i] || B[j])
        {
            ans = 2;
        }

        printf("Case %d: %s\n", kase, str[ans]);
    }
    return 0;
}
