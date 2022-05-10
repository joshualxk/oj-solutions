#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

int N, M;

typedef struct {
    int origin;
    int mod;
} Node;

Node nodes[10000];

int cmp(const void *a, const void *b) {
    Node *n1 = (Node*)a;
    Node *n2 = (Node*)b;
    int diff;
    if (n1->mod == n2->mod) {
        if ((n1->origin & 1) == (n2->origin & 1)) {
            diff = n1->origin > n2->origin ? 1 : -1;
            if (n1->origin & 1) {
                return -diff;
            }  else {
                return diff;
            }
        } else {
            return (n1->origin & 1) ? 0 : 1;
        }
    }
    return n1->mod - n2->mod;
}

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

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
    int i, mod;
    while (readNum(N), readNum(M), N) {
        for (i = 0; i < N; ++i) {
            readNum(nodes[i].origin);
            nodes[i].mod = nodes[i].origin % M;
        }
        qsort(nodes, N, sizeof(Node), cmp);
        printf("%d %d\n", N, M);
        for (i = 0; i < N; ++i) {
            printf("%d\n", nodes[i].origin);
        }
    }
    puts("0 0");
    return 0;
}
