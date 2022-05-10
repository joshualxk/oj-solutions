#include <cstdio>
#include <cmath>

using namespace std;

int K, Q, M;

char states[5][20] = {
    "Illegal state",
    "Illegal move",
    "Move not allowed",
    "Continue",
    "Stop"

};

int col[64] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
};

int row[64] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    5,
    5,
    5,
    5,
    5,
    5,
    5,
    5,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7};

int solve()
{
    int u;
    if (K == Q)
    {
        return 0;
    }
    if (Q == M || M == K)
    {
        return 1;
    }
    if (row[M] == row[Q])
    {
        if (row[K] == row[M] && ((K > Q && M > K) || (K < Q && M < K)))
        {
            return 1;
        }
    }
    else if (col[M] == col[Q])
    {
        if (col[K] == col[M] && ((K > Q && M > K) || (K < Q && M < K)))
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }

    u = 8;
    if (row[M] == row[K])
    {
        u = col[M] - col[K];
    }
    else if (col[M] == col[K])
    {
        u = row[M] - row[K];
    }
    else
    {
        switch (K)
        {
        case 0:
            if (M == 9)
            {
                return 4;
            }
            break;
        case 7:
            if (M == 14)
            {
                return 4;
            }
            break;
        case 56:
            if (M == 49)
            {
                return 4;
            }
            break;
        case 63:
            if (M == 54)
            {
                return 4;
            }
            break;
        }
    }
    if (u == 1 || u == -1)
    {
        return 2;
    }

    return 3;
}

bool readNum(int &num)
{
    int u = getchar();
    do
    {
        if (u == EOF)
        {
            return 0;
        }
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

int main()
{
    while (readNum(K))
    {
        readNum(Q);
        readNum(M);

        puts(states[solve()]);
    }
    return 0;
}
