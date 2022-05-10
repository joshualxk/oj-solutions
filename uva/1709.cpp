#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

int P, A, B, C, D, N;

int main()
{
    int i;
    double maxDec, maxV, u, v;
    double sin1, sin2, cos1, cos2, sina, sinc, cosa, cosc, tmp1, tmp2;

    while (~scanf("%d %d %d %d %d %d", &P, &A, &B, &C, &D, &N))
    {
        maxDec = 0;
        sin1 = sin(A + B);
        cos2 = cos(C + D);
        cos1 = cos(A + B);
        sin2 = sin(C + D);
        sina = sin(A);
        sinc = sin(C);
        cosa = cos(A);
        cosc = cos(C);
        maxV = sin1 + cos2;

        for (i = 2; i <= N; ++i)
        {
            tmp1 = sina * cos1 + sin1 * cosa;
            tmp2 = sinc * cos2 + sin2 * cosc;
            cos1 = cos1 * cosa - sin1 * sina;
            cos2 = cos2 * cosc - sin2 * sinc;
            u = tmp1 + cos2;

            sin1 = tmp1;
            sin2 = tmp2;

            if (u > maxV)
            {
                maxV = u;
            }
            else
            {
                v = maxV - u;
                if (v > maxDec)
                {
                    maxDec = v;
                }
            }
        }
        printf("%lf\n", maxDec  * P);
    }
    return 0;
}
