#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

typedef struct
{
    double x, y;
} point;

point m, a, b, ans;
double minDist;
const double eps = 1e-6;

double dist(point &a, point &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void cal()
{
    double dis, k;
    point tmp;
    dis = dist(m, b);
    if (minDist > dis)
    {
        minDist = dis;
        ans = b;
    }

    if (abs(a.x - b.x) < eps)
    {
        dis = abs(m.x - a.x);
        tmp.x = a.x;
        tmp.y = m.y;

        if (a.y < b.y)
        {
            if (tmp.y < a.y || tmp.y > b.y)
            {
                return;
            }
        }
        else
        {
            if (tmp.y > a.y || tmp.y < b.y)
            {
                return;
            }
        }
    }
    else
    {
        k = (b.y - a.y) / (b.x - a.x);
        tmp.x = (k * (k * a.x - a.y + m.y) + m.x) / (k * k + 1);
        tmp.y = k * (tmp.x - a.x) + a.y;
        dis = dist(tmp, m);

        if (a.x < b.x)
        {
            if (tmp.x < a.x || tmp.x > b.x)
            {
                return;
            }
        }
        else
        {
            if (tmp.x > a.x || tmp.x < b.x)
            {
                return;
            }
        }
    }

    if (minDist > dis)
    {
        minDist = dis;
        ans = tmp;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n;
    while (~scanf("%lf %lf", &m.x, &m.y))
    {
        scanf("%d %lf %lf", &n, &a.x, &a.y);
        minDist = dist(m, a);
        ans = a;
        while (n--)
        {
            scanf("%lf %lf", &b.x, &b.y);
            cal();
            a = b;
        }
        printf("%.4lf\n%.4lf\n", ans.x, ans.y);
    }

    return 0;
}
