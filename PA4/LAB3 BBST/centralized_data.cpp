#include <iostream>
#include <set>
#define MAX_X 8500000
using namespace std;

int main() {
    srand((unsigned)time(nullptr));
    int n, insert_rate, query_times;
    cin >> n >> insert_rate >> query_times;
    set<int> data;
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        int op = rand() % 100;
        if (op < insert_rate) {
            int x;
            while (true) {
                x = rand() % MAX_X;
                if (data.count(x)) continue;
                data.insert(x);
                printf("A %d\n", x);
                break;
            }
            int tmp = i + query_times;
            for (int j = i; j + 1 < n && j < tmp; i++, j++)
                printf("C %d\n", x);
        }
        else {
            if (data.empty()) {
                while (true) {
                    int x = rand() % MAX_X;
                    if (data.count(x)) continue;
                    data.insert(x);
                    printf("A %d\n", x);
                    break;
                }
            }
            else {
                int x = rand() % data.size();
                auto i = data.begin();
                while (x--) i++;
                printf("B %d\n", *i);
            }
        }
    }
}