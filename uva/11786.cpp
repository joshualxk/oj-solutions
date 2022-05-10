#include <cstdio>

using namespace std;

int H[10010], L;

int left[5010], right[5010], ix;

int ans;

int compute(int l, int r) {
    int ret = 0;
    while (H[l] + 1 != H[r]) {
        ++l;
    }
    for (;l < r; ++l) {
        ret += H[r] - H[l];
    }
    
    return ret;
}

int main()
{
    int T, ch, pre;
    int i, j;
    scanf("%d", &T);
    while (T--)
    {
        ch = getchar();
        while (ch != '/' && ch != '\\' && ch != '_')
        {
            ch = getchar();
        }
        L = 1;
        ans = ix = 0;
        pre = '_';
        while (ch == '/' || ch == '\\' || ch == '_')
        {
            if (ch == '_')
            {
                H[L] = H[L - 1];
            }
            else
            {
                if (ch == '/')
                {
                    H[L] = H[L - 1] + 1;
                    if (ix)
                    {
                        for (; ix && H[L] > H[left[ix]]; --ix)
                                ;
                            if (ix) {
                                right[ix] = L;
                            } else {
                                ans += compute(left[1], L);
                            }
                    }
                }
                else
                {
                    if (pre != '\\')
                    {
                        left[++ix] = L;
                    }
                    H[L] = H[L - 1] - 1;
                }
                pre = ch;
            }
            ++L;
            ch = getchar();
        }

        if (pre != '/') {
            --ix;
        }

        for (; ix > 0; --ix) {
            ans += compute(left[ix], right[ix]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
