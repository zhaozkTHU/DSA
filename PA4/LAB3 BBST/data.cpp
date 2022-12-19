#include <iostream>
#include <set>
#define MAX_X 8500000
using namespace std;

int main() {
    srand((unsigned)time(nullptr));
    int n;
    scanf("%d", &n);
    set<int> tree;
    for (int i = 0; i < n; i++) {
        int op = rand() % 3;
        if (op == 0) {
            if (tree.empty()) {
                while (true) {
                    int x = rand() % MAX_X;
                    if (tree.count(x))
                        continue;
                    tree.insert(x);
                    printf("A %d\n", x);
                    break;
                }
            }
            else {
                int x = rand() % tree.size() + 1;
                auto i = tree.begin();
                for (i = tree.begin(); x != 0; x -= 1)
                    i++;
                printf("B %d\n", *i);
            }
        }
        if (op == 1) {
            while (true) {
                int x = rand() % MAX_X;
                if (tree.count(x))
                    continue;
                tree.insert(x);
                printf("A %d\n", x);
                break;
            }
        }
        if (op == 2) {
            int x = rand() % MAX_X;
            printf("C %d\n", x);
        }
    }
}
