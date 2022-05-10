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
#define BUFF_SIZE (1 << 12)
    char buff[BUFF_SIZE + 64];
    int ix;

    int ch;

    void init()
    {
        ix = 0;
        ch = getchar();
    }

    bool readI(int &ival)
    {
        bool negative = 0;
        do
        {
            if (ch == '-')
            {
                negative = 1;
                ch = getchar();
                break;
            }
            else if (ch >= '0' && ch <= '9')
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
        } while (ch >= '0' && ch <= '9');

        if (negative)
        {
            ival = -ival;
        }
        return 1;
    }

    int readStr(char *str)
    {
        while (ch == '\n' || ch == ' ')
        {
            ch = getchar();
        }

        int i;
        for (i = 0; ch != ' ' && ch != '\n'; ++i)
        {
            str[i] = ch;
            ch = getchar();
        }
        str[i] = 0;

        return i;
    }

    void concat(const char *str, int len)
    {
        memmove(buff + ix, str, len);
        ix += len;
    }

    void i2s(int val)
    {
        static char digits[16];
        if (val < 10)
        {
            buff[ix++] = val + '0';
        }
        else
        {
            int i, u;
            for (i = 14, u = val; u; u /= 10, --i)
            {
                digits[i] = u % 10 + '0';
            }
            for (++i; i <= 14; ++i)
            {
                buff[ix++] = digits[i];
            }
        }
    }

    void flush(bool force)
    {
        if (ix >= BUFF_SIZE || (force && ix))
        {
            buff[ix] = 0;

            printf("%s", buff);
            ix = 0;
        }
    }
} io;

int N, M;
int heads[100010];
struct node {
    int v, n;
} nodes[100010];
int ix;

int dfsCnt;
int root;
int sccNum;
int dfn[100010];
int low[100010];
int scc[100010];
int stk[100010];
int stkIx;
int ans;
bool flags[100010];

void tarjan(int cur) {
    dfn[cur] = low[cur] = ++dfsCnt;
    int i, v;
    stk[stkIx++] = cur;
    for (i = heads[cur];i; i=nodes[i].n) {
        v = nodes[i].v;
        if (!dfn[v]) {
            tarjan(v);
            if (low[v] < low[cur]) {
                low[cur] = low[v];
            }
        } else if (dfn[v] <= root) {
            if (flags[scc[v]]) {
                flags[scc[v]] = 0;
                --ans;
            }
        } else if (low[v] < low[cur]) {
            low[cur] = low[v];
        }
    }
    if (dfn[cur] == low[cur]) {
        ++sccNum;
        do {
            v = stk[--stkIx];
            scc[v] = sccNum;
        } while (v != cur);
    }
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, u, v, i;
    io.init();
    io.readI(T);
    while (T--) {
        io.readI(N);
        io.readI(M);

        memset(heads,0,sizeof(heads));
        ix = 0;

        for (i = 0; i < M; ++i) {
            io.readI(u);
            io.readI(v);

            if (u != v) {
                ++ix;
                nodes[ix].v = v;
                nodes[ix].n = heads[u];
                heads[u] = ix;
            }
        }
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(scc, 0, sizeof(scc));
        memset(flags, 0, sizeof(flags));
        dfsCnt = ans = sccNum = 0;
        stkIx = 0;

        for (i = 1; i <= N; ++i) {
            if (!dfn[i]) {
                root = dfsCnt;
                tarjan(i);
                ++ans;
                flags[scc[i]] = 1;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}

