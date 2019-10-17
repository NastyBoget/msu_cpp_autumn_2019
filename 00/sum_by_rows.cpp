#include "timer.h"
#define N 1000
#define M 1000
int main() {
    int arr[N][M] = {0};
    volatile int sum = 0;
    Timer t;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            sum += arr[i][j];
        }
    }
    return 0;
}