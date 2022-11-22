#include <iostream>
using namespace std;

struct Node {
    int x[5];
    Node *left, *right;
    Node() : x({0}), left(nullptr), right(nullptr) {}
};

int d, n;

int cmpx0(const void *a, const void *b) {
    auto p1 = (Node *)a;
    auto p2 = (Node *)b;
    return p1->x[0] - p2->x[0];
}

int cmpx1(const void *a, const void *b) {
    auto p1 = (Node *)a;
    auto p2 = (Node *)b;
    return p1->x[1] - p2->x[1];
}

int cmpx2(const void *a, const void *b) {
    auto p1 = (Node *)a;
    auto p2 = (Node *)b;
    return p1->x[2] - p2->x[2];
}

int cmpx3(const void *a, const void *b) {
    auto p1 = (Node *)a;
    auto p2 = (Node *)b;
    return p1->x[3] - p2->x[3];
}

int cmpx4(const void *a, const void *b) {
    auto p1 = (Node *)a;
    auto p2 = (Node *)b;
    return p1->x[4] - p2->x[4];
}

void build_tree(Node *) {
    
}

int main() {
    scanf("%d%d", &d, &n);
    Node *points = new Node[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%d", &points[i].x[j]);
        }
    }
}