#include <cstdio>

int N, I, J;

int main() {
    int round;
    while (~scanf("%d %d %d", &N, &I, &J)) {
        --I;
        --J;
        for (round = 1; (I ^ 1) != J;++round) {
            I >>= 1;
            J >>= 1;
        }
        printf("%d\n", round);
    }
    return 0;
}