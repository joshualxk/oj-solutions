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

int N, M, S, T, P;

int h1[10010], h2[10010];
int ix;
struct node {
    int u, v, w, n;
} nds[200010];

int dis1[10010], dis2[10010];
bool used[10010];

struct xx {
    int u, w;

    bool operator<(const struct xx &o) const {
        return w > o.w;
    }
};

void dijkstra(int heads[], int dis[], int st) {
    memset(dis, 0x3f, sizeof(dis1));
    memset(used, 0, sizeof(used));

    int u, v, cnt, i;
    struct xx xx, xx2;
    priority_queue<struct xx> pq;
    xx.u = st;
    xx.w = 0;
    pq.push(xx);
    while (!pq.empty()) {
        xx = pq.top();
        pq.pop();

        if (used[xx.u]) {
            continue;
        }
        used[xx.u] = 1;
        dis[xx.u] = xx.w;

        for (i = heads[xx.u]; i; i = nds[i].n) {
            xx2.u = nds[i].v;
            xx2.w = xx.w + nds[i].w;
            pq.push(xx2);
        }
    }

}

int cal() {
    dijkstra(h1, dis1, S);
    dijkstra(h2, dis2, T);

    int ans = -1, i;
    for (i = 1; i <= ix; i += 2) {
        if (dis1[nds[i].u] + dis2[nds[i].v] <= P - nds[i].w) {
            if (nds[i].w > ans) {
                ans = nds[i]. w;
            }
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int kase, i, j, u, v, w;
    io.init();
    io.readI(kase);
    while (kase--) {
        io.readI(N);
        io.readI(M);
        io.readI(S);
        io.readI(T);
        io.readI(P);

        memset(h1, 0, sizeof(h1));
        memset(h2, 0, sizeof(h2));
        ix = 0;

        for (i = 0; i < M; ++i) {
            io.readI(u);
            io.readI(v);
            io.readI(w);

            ++ix;
            nds[ix].u = u;
            nds[ix].v = v;
            nds[ix].w = w;
            nds[ix].n = h1[u];
            h1[u] = ix;

            ++ix;
            nds[ix].v = u;
            nds[ix].w = w;
            nds[ix].n = h2[v];
            h2[v] = ix;
        }

        printf("%d\n", cal());
    }
    return 0;
}
