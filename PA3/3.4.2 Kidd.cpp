#include <iostream>
using namespace std;
using ull = unsigned long long;

struct SegTreeNode {
    uint left, right, lazy;
    ull value;
    SegTreeNode *left_node, *right_node;
    SegTreeNode() : left(0), right(0), lazy(0),
        value(0), left_node(nullptr), right_node(nullptr) {}
    void add(uint l, uint r) {
        if (l > r) exit(EXIT_FAILURE); // DEBUG
        if (left == right) { value += 1; return; }
        if (l == left && r == right) {
            lazy += 1;
            return;
        }
        value += r - l + 1;
        uint mid = (left + right) / 2;
        if (l <= mid && left_node == nullptr) {
            left_node = new SegTreeNode;
            left_node->left = left;
            left_node->right = mid;
        }
        if (mid + 1 <= r && right_node == nullptr) {
            right_node = new SegTreeNode;
            right_node->left = mid + 1;
            right_node->right = right;
        }
        if (l <= mid && mid + 1 <= r) {
            left_node->add(l, mid);
            right_node->add(mid + 1, r);
        }
        if (r <= mid) left_node->add(l, r);
        if (mid + 1 <= l) right_node->add(l, r);
    }
    ull query(uint l, uint r) {
        if (l > r) exit(EXIT_FAILURE); // DEBUG
        if (left == right) {
            value += lazy;
            lazy = 0;
            return value;
        }
        if (l == left && r == right) {
            return value + ull(right - left + 1) * ull(lazy);
        }
        if (value == 0) return ull(r - l + 1) * ull(lazy);
        ull res = 0;
        uint mid = (left + right) / 2;

        // 懒惰标记下移
        if (left_node == nullptr) {
            left_node = new SegTreeNode;
            left_node->left = left;
            left_node->right = mid;
        }
        left_node->lazy += lazy;
        if (right_node == nullptr) {
            right_node = new SegTreeNode;
            right_node->left = mid + 1;
            right_node->right = right;
        }
        right_node->lazy += lazy;
        value += ull(lazy) * ull(right - left + 1);
        lazy = 0;

        if (l <= mid && mid + 1 <= r) {
            res += left_node->query(l, mid);
            res += right_node->query(mid + 1, r);
        }
        if (r <= mid) res += left_node->query(l, r);
        if (mid + 1 <= l) res += right_node->query(l, r);

        return res;
    }
    ~SegTreeNode() {
        if (left_node) {
            delete left_node;
        }
        if (right_node) {
            delete right_node;
        }
    }
};

int main() {
    uint n, m;
    scanf("%u%u", &n, &m);
    SegTreeNode *root = new SegTreeNode;
    root->left = 1;
    root->right = n;
    for (int i = 0; i < m; i++) {
        char op;
        scanf(" %c", &op);
        switch (op) {
            case 'H': {
                uint l, r;
                scanf("%u%u", &l, &r);
                root->add(l, r);
                break;
            }
            case 'Q': {
                uint l, r;
                scanf("%u%u", &l, &r);
                printf("%llu\n", root->query(l, r));
                break;
            }
            default: exit(EXIT_FAILURE);
        }
    }
    delete root;
    return 0;
}