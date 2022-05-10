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

#define MAXN 10200
#define HEAD 1
#define TAIL 2
int M, N, M0;
int dp[MAXN + 10];
struct node
{
    int val, pre;
} nodes[1 << 14];
int ix;

inline void insert(int p, int f)
{
    static deque<int> dq;
    dq.clear();

    int cur, u, v, pre;
    for (cur = TAIL; cur; cur = nodes[cur].pre)
    {
        u = nodes[cur].val;
        v = u + p;
        if (v <= M)
        {
            if (!dp[v])
            {
                dp[v] = dp[u] + f;
                dq.push_back(v);
            }
            else if (dp[u] + f > dp[v])
            {
                dp[v] = dp[u] + f;
            }
        }
    }
    if (!dq.empty())
    {
        for (cur = TAIL; cur && !dq.empty(); cur = nodes[cur].pre)
        {
            u = nodes[cur].val;
            v = dq.front();
            for (pre = nodes[cur].pre; nodes[pre].val > v; pre = nodes[pre].pre)
            {
                cur = pre;
            }
            v = dq.front();
            dq.pop_front();
            ++ix;
            nodes[ix].pre = nodes[cur].pre;
            nodes[ix].val = v;
            nodes[cur].pre = ix;
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, j, p, f;
    while (readInt(M0))
    {
        readInt(N);
        memset(dp, 0, sizeof dp);
        M = M0 > 1800 ? M0 + 200 : M0;
        nodes[TAIL].val = M;
        nodes[TAIL].pre = HEAD;
        ix = TAIL;
        dp[M] = -1;

        for (i = 0; i < N; ++i)
        {
            readInt(p);
            readInt(f);
            insert(p, f);
        }
        p = 0;
        for (i = TAIL; i; i = nodes[i].pre)
        {
            j = nodes[i].val;
            if (dp[j] > p)
            {
                if (j <= M0 || (j > 2000))
                    p = dp[j];
            }

        }
        printf("%d\n", p);
    }
    return 0;
}
