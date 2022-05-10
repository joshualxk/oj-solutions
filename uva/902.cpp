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
            if (ch == EOF) {
                return 0;
            }
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

    int readStr(char *str)
    {
        while (ch <= 32)
        {
            ch = getchar();
        }

        int i;
        for (i = 0; ch > 32; ++i)
        {
            str[i] = ch;
            ch = getchar();
        }
        str[i] = 0;

        return i;
    }

} io;


int N;
char str[1000000];
int L;
map<int64_t, int> mm;

int64_t po[12];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, ix, u;
    int64_t mak, m;

    po[1] = 1;
    for (i = 2; i < 12; ++i) {
        po[i] = po[i - 1] * 26;
    }

    io.init();
    while (io.readI(N)) {
        L = io.readStr(str);
        mm.clear();
        m = 0;
        for (i = 0; i < N; ++i) {
            m = (m * 26 + str[i] - 'a');
        }
        mak = mm[m] = 1;
        ix = N;
        for (; i < L; ++i) {
            m = ((m -  (str[i - N] - 'a') * po[N]) * 26 + str[i] - 'a');
            if((u = ++mm[m]) > mak) {
                mak = u;
                ix = i + 1;
            }
        }

        str[ix] = 0;
        puts(str + ix - N);
        // printf("%d %d\n", ix, mak);
    }
    return 0;
}
