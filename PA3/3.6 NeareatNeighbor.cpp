#include <iostream>
using namespace std;
int d, n;
struct Point {
    int x[5];
};

struct TreeNode {
    int dir;
    int left_node, right_node;
    TreeNode *left, *right;
    TreeNode() : left(nullptr), right(nullptr) {};
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
        return a_->x[4] - b_->x[4];
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
    if (right - left < 10) {
        root->left_node = left; root->right_node = right;
        root->dir = dir;
        root->left = nullptr; root->right = nullptr;
        return;
    }
    int mid = (left + right) >> 1;
    cmp::sort_dir(points + left, right - left + 1, dir);

    int new_dir = (dir == d - 1) ? 0 : dir + 1;
    root->left_node = mid; root->right_node = mid;
    root->dir = dir;
    root->left = new TreeNode;
    build_tree(root->left, left, mid - 1, new_dir);
    root->right = new TreeNode;
    build_tree(root->right, mid + 1, right, new_dir);
}

void query(Point *query_point, long long &res, TreeNode *root) {
    for (int i = root->left_node; i <= root->right_node; i++) {
        int dir = root->dir;
        long long min_distance =
            (long long)(query_point->x[dir] - points[i].x[dir]) *
            (long long)(query_point->x[dir] - points[i].x[dir]);
        if (min_distance < res) {
            long long new_res = calculate(query_point, &points[i]);
            if (new_res < res) res = new_res;
        }
        if (query_point->x[dir] < points[i].x[dir]) {
            if (root->left)
                query(query_point, res, root->left);
            if (min_distance < res && root->right)
                query(query_point, res, root->right);
        }
        else {
            if (root->right)
                query(query_point, res, root->right);
            if (min_distance < res && root->left)
                query(query_point, res, root->left);
        }
    }
    return;
}

int main() {
    scanf("%d%d", &d, &n);
    points = new Point[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            scanf("%d", &points[i].x[j]);
    TreeNode *root(new TreeNode);
    build_tree(root, 0, n - 1, 0);
    int q; scanf("%d", &q);
    Point *query_point = new Point;
    while (q--) {
        for (int i = 0; i < d; i++)
            scanf("%d", &query_point->x[i]);
        long long res = calculate(query_point, &points[root->left_node]);
        query(query_point, res, root);
        printf("%lld", res);
        if (q != 0) printf("\n");
    }
    delete query_point;
}