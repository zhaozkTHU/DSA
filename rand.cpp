#include <iostream>
#include <ctime>
using namespace std;

int main() {
    srand((unsigned)time(nullptr));
    for (int i = 0; i < 10,000,000; i++) {
        printf("%d", rand() % 2);
    }
    printf("\n");
}