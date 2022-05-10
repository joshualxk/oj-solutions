#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

char op1[210];
char op2[210];

void compute() {
    int carry = 0;
    int sum, digit, i, j;
    for (i = 0; op1[i] && op2[i]; ++i) {
        sum = op1[i] + op2[i] + carry - 2 * '0';
        if (sum > 9) {
            carry = 1;
            digit = sum - 10;
        } else {
            carry = 0;
            digit = sum;
        }
        op1[i] = '0' + digit;
    }
    for (; op1[i] || op2[i]; ++i) {
        sum = op1[i] + op2[i] + carry - '0';
        if (sum > 9) {
            carry = 1;
            digit = sum - 10;
        } else {
            carry = 0;
            digit = sum;
        }
        op1[i] = '0' + digit;
    }
    if (carry) {
        op1[i++] = '1';
    }
    for (i = 0; op1[i] == '0'; ++i);
    puts(op1 + i);

}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
    int N;
    scanf("%d", &N);
    while (N--) {
        memset(op1, 0, sizeof op1);
        memset(op2, 0, sizeof op2);
        scanf("%s %s", op1, op2);
        compute();
    }
    return 0;
}
