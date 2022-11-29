#include <iostream>
#include <ctime>
using namespace std;

int main() {
    srand((int)time(nullptr));
    int d = rand() % 4 + 2;
    int n = rand() % 100;
    printf("%d %d\n", d, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++)
            printf("%d ", rand() % 100);
        printf("\n");
    }
    n = rand() % 100;
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++)
            printf("%d ", rand() % 100);
        printf("\n");
    }
}