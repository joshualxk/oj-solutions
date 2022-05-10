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

int total, transfer, lastTranser, second;
char buff[1 << 16];

inline int i2s(char *buff, int ival)
{
    static char tmp[16];
    if (!ival)
    {
        buff[0] = '0';
        return 1;
    }

    int i, len = 0;
    for (i = 14; ival; --i)
    {
        tmp[i] = ival % 10;
        ival /= 10;
    }
    for (++i; i <= 14; ++i)
    {
        buff[len++] = '0' + tmp[i];
    }
    return len;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 0, u, ix;
    while (readInt(total), total)
    {
        printf("Output for data set %d, %d bytes:\n", ++T, total);
        transfer = 0;
        lastTranser = 0;
        ix = 0;
        for (second = 1;; ++second)
        {
            readInt(u);
            transfer += u;
            lastTranser += u;
            if (second % 5 == 0)
            {
                if (!lastTranser)
                {
                    strcpy(buff + ix, "   Time remaining: stalled\n");
                    ix += 27;
                }
                else
                {
                    u = total - transfer;
                    u = (u * 5 + lastTranser - 1) / lastTranser;
                    strcpy(buff + ix, "   Time remaining: ");
                    ix += 19;
                    ix += i2s(buff + ix, u);
                    strcpy(buff + ix, " seconds\n");
                    ix += 9;
                    lastTranser = 0;
                }
            }
            if (transfer == total)
            {
                if (ix)
                {
                    buff[--ix] = 0;
                    puts(buff);
                }
                printf("Total time: %d seconds\n\n", second);
                break;
            }
        }
    }
    return 0;
}
