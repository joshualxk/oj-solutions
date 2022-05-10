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

    bool skip() {
        while (ch == ' ' || ch == '\n') {
            ch = getchar();
        }
        return ch != EOF;
    }

    bool readI(int &ival)
    {
        do
        {
            if (ch >= '0' && ch <= '9')
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

int N;
int M;

bool edges[32][32];
bool vis[32];

struct node {
    int u, d;
};

int cal(int u, int v) {
    int i, ret = M - 1;
    if (!u) {
        return M;
    }
    if (!v) {
        return ret;
    }
    struct node nd, nd2;
    queue<struct node> q;
    nd.u = u;
    nd.d = v;
    q.push(nd);
    memset(vis, 0, sizeof(vis));
    vis[u] = 1;

    while (!q.empty()) {
        nd = q.front();
        q.pop();

        for (i = 1; i <= M; ++i) {
            if (edges[nd.u][i] && !vis[i]) {
                vis[i] = 1;
                --ret;
                nd2.u = i;
                nd2.d = nd.d - 1;
                if (nd2.d > 0) {
                    q.push(nd2);
                }
            }
        }
    }
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int kase = 0, i, u, v, p, q;
    map<int, int> m;
    while (1) {
        io.readI(N);
        if (!N) {
            break;
        }
        m.clear();
        M = 0;
        memset(edges, 0, sizeof(edges));
        for (i = 0; i < N; ++i) {
            io.readI(u);
            io.readI(v);

            p = m[u];
            if (!p) {
                p = m[u] = ++M;
            }

            q = m[v];
            if (!q) {
                q = m[v] = ++M;
            }

            edges[p][q] = 1;
            edges[q][p] = 1;
        }

        while (1) {
            io.readI(u);
            io.readI(v);
            if (!u && !v) {
                break;
            }
            
            io.concat("Case ", 5);
            io.i2s(++kase);
            io.buff[io.ix++] = ':';
            io.buff[io.ix++] = ' ';
            io.i2s(cal(m[u], v));
            io.concat(" nodes not reachable from node ", 31);
            io.i2s(u);
            io.concat(" with TTL = ", 12);
            io.i2s(v);
            io.buff[io.ix++] = '.';
            io.buff[io.ix++] = '\n';
            io.flush(0);
        }
    }
    io.flush(1);
    return 0;
}
