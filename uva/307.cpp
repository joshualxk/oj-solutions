#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 105

int N;
int sticks[MAXN];
bool used[MAXN];

inline bool readNum(int &num)
{
    int u = getchar();
    do
    {
        if (u >= '0' && u <= '9')
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

    return 1;
}

bool cmp(int a, int b)
{
    return a > b;
}

int ansN;
int ans;

bool check(int st, int cnt, int cur)
{
    int i, u;
    if (cnt == ansN)
    {
        return 1;
    }

    for (i = st; i < N; ++i)
    {
        if (used[i])
        {
            continue;
        }

        u = cur + sticks[i];
        if (u == ans)
        {
            used[i] = 1;
            if (check(0, cnt + 1, 0))
            {
                return 1;
            }

            used[i] = 0;
            return 0;
        }
        else if (u < ans)
        {
            used[i] = 1;
            if (check(i + 1, cnt, u))
            {
                return 1;
            }
            used[i] = 0;

            if (cur == 0)
            {
                return 0;
            }

            for (; i + 1 < N && sticks[i + 1] == sticks[i]; ++i)
                ;
        }
    }

    return 0;
}

int main()
{
    int i, total;
    while (readNum(N) && N)
    {
        total = 0;
        for (i = 0; i < N; ++i)
        {
            readNum(sticks[i]);
            total += sticks[i];
        }
        sort(sticks, sticks + N, cmp);
        memset(used, 0, sizeof used);

        for (i = total / sticks[0]; i > 1; --i)
        {
            if (total % i)
            {
                continue;
            }
            ans = total / i;
            ansN = i - 1;
            if (check(0, 0, 0))
            {
                break;
            }
        }
        if (i == 1)
        {
            ans = total;
        }
        printf("%d\n", ans);
    }
    return 0;
}
