#include <iostream>
#include <bits/stl_algo.h>
#define null_coordinate 2147483647
using namespace std;

int times;

int d, n;
struct Point {
    int x[5];
};

struct TreeNode {
    int dir;
    Point *value;
    TreeNode *left, *right, *parent;
    TreeNode() : value(new Point), left(nullptr), right(nullptr), parent(nullptr) {};
};

Point *points;

long long calculate(Point *a, Point *b) {
    long long res = 0;
    for (int i = 0; i < d; i++)
        res += (long long)(a->x[i] - b->x[i]) * (long long)(a->x[i] - b->x[i]);
    return res;
}

namespace cmp {
    int cmp0(const void *a, const void *b) {
        auto a_ = (Point *)a;
        auto b_ = (Point *)b;
        return a_->x[0] - b_->x[0];
    }

    int cmp1(const void *a, const void *b) {
        auto a_ = (Point *)a;
        auto b_ = (Point *)b;
        return a_->x[1] - b_->x[1];
    }

    int cmp2(const void *a, const void *b) {
        auto a_ = (Point *)a;
        auto b_ = (Point *)b;
        return a_->x[2] - b_->x[2];
    }

    int cmp3(const void *a, const void *b) {
        auto a_ = (Point *)a;
        auto b_ = (Point *)b;
        return a_->x[3] - b_->x[3];
    }

    int cmp4(const void *a, const void *b) {
        auto a_ = (Point *)a;
        auto b_ = (Point *)b;
        return a_->x[1] - b_->x[4];
    }

    void sort_dir(Point *base, int n, int dir) {
        switch (dir) {
            case 0: {
                qsort(base, n, sizeof(Point), cmp0);
                break;
            }
            case 1: {
                qsort(base, n, sizeof(Point), cmp1);
                break;
            }
            case 2: {
                qsort(base, n, sizeof(Point), cmp2);
                break;
            }
            case 3: {
                qsort(base, n, sizeof(Point), cmp3);
                break;
            }
            case 4: {
                qsort(base, n, sizeof(Point), cmp4);
                break;
            }
            default: exit(EXIT_FAILURE);
        }
    }
}

void build_tree(TreeNode *root, int left, int right, int dir) {
    if (left > right || dir > d) exit(EXIT_FAILURE);
    if (left == right) {
        root->value = &points[left]; root->dir = dir;
        root->left = nullptr; root->right = nullptr;
        return;
    }
    int mid = (left + right) >> 1;
    cmp::sort_dir(points + left, right - left + 1, dir);

    int new_dir = dir == d - 1 ? 0 : dir + 1;
    root->value = &points[mid];
    root->dir = dir;
    if (mid == left) {
        root->left = nullptr;
    }
    else {
        root->left = new TreeNode;
        root->left->parent = root;
        build_tree(root->left, left, mid - 1, new_dir);
    }
    root->right = new TreeNode;
    root->right->parent = root;
    build_tree(root->right, mid + 1, right, new_dir);
}

void query(Point *point, long long &res, TreeNode *root) {
    times++;
    int dir = root->dir;
    long long min_distance =
        (long long)(point->x[dir] - root->value->x[dir]) *
        (long long)(point->x[dir] - root->value->x[dir]);
    if (min_distance < res) {
        long long new_res = calculate(point, root->value);
        if (new_res < res) res = new_res;
    }
    if (point->x[dir] < root->value->x[dir]) {
        if (root->left)
            query(point, res, root->left);
        if (min_distance < res && root->right)
            query(point, res, root->right);
    }
    else {
        if (root->right)
            query(point, res, root->right);
        if (min_distance < res && root->left)
            query(point, res, root->left);
    }
    return;
}

int main() {
    scanf("%d%d", &d, &n);
    points = new Point[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            scanf("%d", &points[i].x[j]);
    TreeNode *root(new TreeNode); root->parent = nullptr;
    build_tree(root, 0, n - 1, 0);
    int q; scanf("%d", &q);
    Point *point = new Point;
    while (q--) {
        for (int i = 0; i < d; i++)
            scanf("%d", &point->x[i]);
        long long res = calculate(point, root->value);
        times = 0;
        query(point, res, root);
        printf("%lld %d", res, times);
        if (q != 0) printf("\n");
    }
    delete point;
}