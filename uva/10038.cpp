#include <cstdio>
#include <cstring>

bool readNum(int &num)
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
    if (negative) {
        num = -num;
    }

    return 1;
}

int N;
char used[3010];

int main()
{
    int i;
    int pre, cur, diff;
    while (readNum(N))
    {
        memset(used, 0, N);
        readNum(pre);
        for (i = 1; i < N; ++i)
        {
            readNum(cur);
            diff = cur - pre;
            pre = cur;
            if (diff < 0)
            {
                diff = -diff;
            }
            if (diff < N && !used[diff - 1])
            {
                used[diff - 1] = 1;
            }
            else
            {
                for (int j = i + 1; j < N; ++j)
                {
                    readNum(cur);
                }
                break;
            }
        }
        puts(i == N ? "Jolly" : "Not jolly");
    }
    return 0;
}