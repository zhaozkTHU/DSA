#include <iostream>
#include <set>
#define MAX_X 8500000
using namespace std;

int main() {
    srand((unsigned)time(nullptr));
    int n;
    int insert_rate;
    int delete_rate;
    scanf("%d%d%d", &n, &insert_rate, &delete_rate);
    set<int> tree;
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        int op = rand() % 100;
        if (op >= insert_rate && op < delete_rate + insert_rate) {
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
                int x = rand() % tree.size();
                auto i = tree.begin();
                while(x--) i++;
                printf("B %d\n", *i);
            }
        }
        else if (op < insert_rate) {
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
            int x = rand() % MAX_X;
            printf("C %d\n", x);
        }
    }
}
