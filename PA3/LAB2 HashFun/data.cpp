#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;

struct Data {
    string id;
    int number;
};

// 三次参数
// 100000 100000 0
// 10000 5000 1
// 100000 200000 0

int main() {
    int insert, query, distribution;
    printf("Please input insert time\n");
    scanf("%d", &insert);
    printf("Please input query time\n");
    scanf("%d", &query);
    printf("Please input distribution method\n");
    printf("0: evenly distributed  1: centralized distribution\n");
    scanf("%d", &distribution);

    srand((unsigned)time(nullptr));
    freopen("./dataset/poj.txt", "r", stdin);
    freopen("./data.in", "w", stdout);
    int a, c, d;
    string b;
    vector<Data> data;
    while (cin >> a >> b >> c >> d) {
        data.push_back(Data{ b, c });
    }
    if (distribution == 1) {
        for (int i = 0; i < insert; i++) {
            int tmp = rand() % data.size();
            printf("0 %s %d\n", data[tmp].id.c_str(), data[tmp].number);
        }
        for (int i = 0; i < query; i++) {
            int tmp = rand() % data.size();
            printf("1 %s\n", data[tmp].id.c_str());
        }
    }
    else {
        vector<int> order;
        for (int i = 0; i < insert; i++) order.push_back(0);
        for (int i = 0; i < query; i++) order.push_back(1);
        auto rng = default_random_engine{};
        shuffle(order.begin(), order.end(), rng);
        for (auto i = order.begin(); i != order.end(); i++) {
            if (*i == 0) {
                int tmp = rand() % data.size();
                printf("0 %s %d\n", data[tmp].id.c_str(), data[tmp].number);
            }
            else {
                int tmp = rand() % data.size();
                printf("1 %s\n", data[tmp].id.c_str());
            }
        }
    }
    cout << "2" << endl;
}