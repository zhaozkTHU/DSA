#include <iostream>
#include <ctime>
using namespace std;

int main() {
    srand((unsigned)time(nullptr));
    for (int i = 0; i < 500000; i++) {
        printf("%c", 'a' + rand() % 26);
    }
    printf("\n");
}