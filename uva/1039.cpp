#include <cstdio>
#include <cstring>

using namespace std;

#define HEAD 0
#define MAXN 15000
#define M 1024

struct DLX {
    int u[MAXN], d[MAXN], l[MAXN], r[MAXN];
    int row[MAXN], col[MAXN];
    int colSz[M + 1];
    int sz;
    int ansN;
    int ans[256];

    void init() {
        ansN = 0;
        for (int i  = 0; i <=M; ++i) {
            u[i] = i;
            d[i] = i;
            l[i] = i - 1;
            r[i] = i + 1;
        }

        sz = M + 1;
        
        l[0] = M;
        r[M] = 0;
        memset(colSz, 0, sizeof(colSz));
    }

    void addRow(int R, int conds[4]) {
        int first = sz;
        for (int i = 0; i < 4; ++i) {
            int cond = conds[i];
            u[sz] = u[cond];
            d[sz] = cond;
            l[sz] = sz - 1;
            r[sz] = sz + 1;

            d[u[cond]] = sz;
            u[cond] = sz;

            col[sz] = cond;
            row[sz] = R;

            colSz[cond]++;

            sz++;
        }
        l[first] = sz - 1;
        r[sz - 1] = first;
    }

    void remove(int C) {
        r[l[C]] = r[C];
        l[r[C]] = l[C];
        for (int i = d[C]; i != C; i = d[i]) {
            for (int j = r[i]; j != i; j = r[j]) {
                d[u[j]] = d[j];
                u[d[j]] = u[j];
                colSz[col[j]]--;
            }
        }
    }

    void restore(int C) {
        for (int i = u[C]; i != C; i =u[i]) {
            for (int j = l[i]; j != i; j =l[j]) {
                d[u[j]] = j;
                u[d[j]] = j;
                colSz[col[j]]++;
            }
        }
        r[l[C]] = C;
        l[r[C]] = C;
    }

    bool dance(int step) {
        int i,j;
        if (r[HEAD] == HEAD) {
            ansN = step;
            return 1;
        }

        int C = r[HEAD];
        for (i = r[HEAD]; i != HEAD; i=r[i]) {
            if (colSz[i] < colSz[C]) {
                C = i;
            }
        }

        remove(C);
        for (i = d[C]; i != C; i= d[i]) {
            ans[step] = row[i];
            for (j = r[i]; j != i; j = r[j]) {
                remove(col[j]);
            }
            if (dance(step + 1)) {
                return 1;
            }
            for (j = l[i]; j != i; j = l[j]) {
                restore(col[j]);
            }
        }
        restore(C);
        return 0;
    }

    void printAns() {
        static char sudoku[16][17] = {0};
        int i, r, c, n;
        for (i = 0; i < ansN; ++i) {
            r = ans[i] >> 8;
            c = (ans[i] >> 4) & 0xf;
            n = ans[i] & 0xf;

            sudoku[r][c] = 'A' + n;
        }
        for (i = 0; i < 16;++i) {
            puts(sudoku[i]);
        }
    }
} dlx;

void addRow(int r, char *str) {
    int i, j;
    static int arr[4];
    for (i = 0 ; i < 16; ++i) {
        for (j = 0; j < 16; ++j) {
            if (str[i] == '-' || str[i] == 'A' + j) {
                arr[0] = 1 + r * 16 + i;
                arr[1] = 1 + 256 + r * 16 + j;
                arr[2] = 1 + 512 + i * 16 + j;
                arr[3] = 1 + 768 + (r / 4 * 4 + i / 4) * 16 + j;
                dlx.addRow((r << 8) | (i << 4) | j, arr);
            }
        }
    }
}

int main(){
    int i, Kase = 0;
    char str[17];
    while (~scanf("%s", str)) {
        dlx.init();
        if (Kase) {
            putchar('\n');
        }

        addRow(0, str);
        for (i = 1; i < 16; ++i) {
            scanf("%s", str);
            addRow(i, str);
        }

        dlx.dance(0);

        dlx.printAns();

        Kase = 1;
    }
    return 0;
}
