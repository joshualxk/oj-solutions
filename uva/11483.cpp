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
        ch  = getchar();

        int i;
        for (i = 0; ch > '\n'; ++i)
        {
            if (ch == '"' || ch == '\\') {
                str[i++] = '\\';
            }
            str[i] = ch;
            ch = getchar();
        }
        str[i] = 0;

        return i;
    }

} io;

int N;
char str[210];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i,kase;
    io.init();
    for (kase = 1;;++kase) {
        io.readI(N);
        if (!N) {
            break;
        }
        printf("Case %d:\n#include<string.h>\n#include<stdio.h>\nint main()\n{\n", kase);
        for (i = 0; i < N; ++i) {
            io.readStr(str);
            printf("printf(\"%s\\n\");\n", str);
        }
        puts("printf(\"\\n\");\nreturn 0;\n}");
    }

    return 0;
}
