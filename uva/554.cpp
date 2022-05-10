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

    int readStr(char *str)
    {
        while (ch <= '\n')
        {
            ch = getchar();
        }

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

int arr[100];
int sz;
char str[256], str2[256];

int hach(char str[], int st, int ed)
{
    int i, m = 0;
    for (i = st; i < ed; ++i)
    {
        m = (m * 26 + str[i] - 'a') % 10000019;
    }
    return m;
}

bool conv(int offset)
{
    int ch;
    int i, j, m;
    int pre = 0;
    bool ret = 0;
    for (i = 0; str[i]; ++i)
    {
        ch = (str[i] == ' ' ? 64 : str[i]) + offset;
        if (ch > 'Z')
        {
            ch -= 27;
        }
        if (ch < 'A')
        {
            ch = ' ';
            if (pre < i && !ret)
            {
                m = hach(str2, pre, i);
                for (j = 0; j < sz; ++j)
                {
                    if (arr[j] == m)
                    {
                        ret = 1;
                        break;
                    }
                }
            }
            pre = i + 1;
        }

        str2[i] = ch;
    }
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, l;
    io.init();
    for (sz = 0;; ++sz)
    {
        l = io.readStr(str);
        if (str[0] == '#')
        {
            break;
        }
        arr[sz] = hach(str, 0, l);
    }
    sort(arr, arr + sz);
    l = io.readStr(str);
    str2[l] = 0;
    for (i = 1; i <= 26; ++i)
    {
        if (conv(i))
        {
            break;
        }
    }

    for (; l >= 0; --l) {
        if (str2[l - 1] != ' ') {
            break;
        }
    }
    str2[l] = 0;

    for (i = 0; i + 60 < l;) {
        for (j = i + 60; str2[j] != ' '; --j);
        str2[j] ='\n';
        i = j + 1;
    }
    puts(str2);


    return 0;
}
