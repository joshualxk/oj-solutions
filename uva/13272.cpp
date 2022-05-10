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

inline void toStr(char *buf, int len, int ival) {
    int i;
    for (i = 14; ival; --i) {
        buf[--len] = '0' + ival % 10;
        ival /= 10;
    }
}

int L;
int ans[100010];
int pairs[256];

int stack[100010][2], ix;
int stack2[50010], ix2;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int T, kase, i, j, u;
    char *buf = (char *) stack;;
    register int ch;
    stack[0][0] = -1;
    pairs['}'] = '{';
    pairs[']'] = '[';
    pairs['>'] = '<';
    pairs[')'] = '(';

    readInt(T);
    for (kase = 1; kase <= T; ++kase)
    {
        ch = getchar();
        while (ch == ' ' || ch == '\n')
        {
            ch = getchar();
        }

        ix = 0;
        ix2 = 0;
        for (i = 0; ch != '\n' && ch != EOF; ++i)
        {
            ans[i] = 0;

            if (pairs[ch])
            {
                if (stack[ix][0] == pairs[ch])
                {
                    ans[i] = i - stack[ix--][1] + 1;
                    stack2[ix2++] = i;
                }
                else
                {
                    ix = 0;
                }
            }
            else
            {
                stack[++ix][0] = ch;
                stack[ix][1] = i;
            }

            ch = getchar();
        }
        L = i;
        ans[L] = 0;
        for (i = ix2 - 1; i >= 0; --i)
        {
            j = stack2[i];
            u = j - ans[j] + 1;
            ans[u] = ans[j] + ans[j + 1];
            ans[j] = 0;
        }

        i = 5;
        printf("Case %d:\n", kase);
        ix = 0;
        for (i = 0; i < L; ++i)
        {
            if (ans[i] < 10) {
                buf[ix++] = '0' + ans[i];
            } else if (ans[i] < 100) {
                toStr(buf + ix, 2, ans[i]);
                ix += 2;
            } else if (ans[i] < 1000) {
                toStr(buf + ix, 3, ans[i]);
                ix += 3;
            } else if (ans[i] < 10000) {
                toStr(buf + ix, 4, ans[i]);
                ix += 4;
            } else if (ans[i] < 100000) {
                toStr(buf + ix, 5, ans[i]);
                ix += 5;
            } else {
                toStr(buf + ix, 6, ans[i]);
                ix += 6;
            }
            buf[ix++] = '\n';
        }
        buf[--ix] = 0;
        puts(buf);
    }

    return 0;
}
