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
int heads[1000];
int vs[2010];
int ns[2010];
int ws[2010];
int ix;
bool inq[1000];
int cnt[1000];
int dis[1000];
bool spfa() {
    queue<int> q;
    memset(inq, 0, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    memset(dis, 0x3f, sizeof(dis));

    dis[0] = 0;
    cnt[0] = 1;
    q.push(0);
    int u, v, i;
    while (!q.empty()) {
        u = q.front();
        q.pop();

        inq[u] = 0;

        for (i = heads[u]; i; i = ns[i]) {
            v = vs[i];
            if (dis[v] > dis[u] + ws[i]) {
                dis[v] = dis[u] + ws[i];

                cnt[v] = cnt[u] + 1;
                if (cnt[v] > N) {
                    return 1;
                }

                if (!inq[v]) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int kase, i, u, v, w;
    io.init();
    io.readI(kase);
    while (kase--) {
        io.readI(N);
        io.readI(M);
        memset(heads, 0, sizeof(heads));
        ix = 0;

        for (i = 0; i < M; ++i) {
            io.readI(u);
            io.readI(v);
            io.readI(w);

            ++ix;
            vs[ix] = v;
            ns[ix] = heads[u];
            ws[ix] = w;
            heads[u] = ix;
        }

        puts(spfa() ? "possible" : "not possible");
    }
    return 0;
}
