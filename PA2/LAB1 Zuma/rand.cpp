#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main() {
    // srand((unsigned)time(nullptr));
    // for (int i = 0; i < 200000; i++) {
    //     if (i % 2 == 0) {
    //         printf("AA");
    //     }
    //     else {
    //         printf("BB");
    //     }
    // }
    // printf("\n500000\n");
    // for (int i = 0; i < 500000; i++) {
    //     if (i % 2 == 0) {
    //         printf("0 A\n");
    //     }
    //     else {
    //         printf("0 B\n");
    //     }
    // }

    for (int i = 0; i < 500000; i++) {
        printf("%c", 'A' + i % 26);
    }
    printf("\n");
    printf("%d\n", 500000);
    for (int i = 0; i < 500000; i++)
        printf("0 %c\n", 'Z' - i % 26);
}