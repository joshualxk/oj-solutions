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

int N, M;
int books[10000];

bool find(int l, int r, int val) {
    int mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (books[mid] == val) {
            return 1;
        } else if (books[mid] > val) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return books[l] == val;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int i, u;
    while (readInt(N)) {
        for (i = 0; i < N; ++i) {
            readInt(books[i]);
        }
        readInt(M);
        sort(books, books + N);
        int mid = lower_bound(books, books + N, M / 2) - books;
        for (;books[mid] <= M; ++mid) {
            if (find(0, mid - 1, M - books[mid])) {
                u = books[mid];
                break;
            }
        }
        printf("Peter should buy books whose prices are %d and %d.\n\n", M - u, u);
    }
    return 0;
}
