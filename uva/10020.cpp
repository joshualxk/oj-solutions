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

struct pa1r
{
    int l, r;
} ps[1000000];
int sz;
int M;

vector<int> ans;

int cmp(const void *ptr0, const void *ptr1)
{
    struct pa1r *p0 = (struct pa1r *)ptr0;
    struct pa1r *p1 = (struct pa1r *)ptr1;

    if (p0->l != p1->l)
    {
        return p0->l - p1->l;
        ;
    }
    return p0->r - p1->r;
}

bool cal()
{
    int cur = 0, mak, ix, u;
    int i, j;
    ans.clear();
    i = 0;
    while (cur < M)
    {
        mak = cur;
        ix = -1;
        for (; i < sz; ++i)
        {
            if (ps[i].l > cur)
            {
                break;
            }
            if (ps[i].r > mak)
            {
                mak = ps[i].r;
                ix = i;
            }
        }
        if (ix < 0)
        {
            return 0;
        }
        ans.push_back(ix);
        cur = ps[ix].r;
    }

    return 1;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, kase, u, v, st, ed, i;
    io.init();
    io.readI(T);
    for (kase = 0; kase < T; ++kase)
    {
        io.readI(M);
        sz = 0;
        st = 0;
        ed = M;
        while (1)
        {
            io.readI(u);
            io.readI(v);
            if (!u && !v)
            {
                break;
            }
            if (u >= ed || v <= st || u > v)
            {
            }
            else
            {
                ps[sz].l = u;
                ps[sz].r = v;
                ++sz;
            }
        }
        qsort(ps, sz, sizeof(ps[0]), cmp);
        cal();

        if (kase)
        {
            putchar('\n');
        }
        if (cal())
        {
            printf("%d\n", ans.size());
            for (i = 0; i < ans.size(); ++i)
            {
                printf("%d %d\n", ps[ans[i]].l, ps[ans[i]].r);
            }
        }
        else
        {
            printf("0\n");
        }
    }
    return 0;
}
