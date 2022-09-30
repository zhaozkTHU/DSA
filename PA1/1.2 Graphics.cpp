#include<iostream>
using namespace std;

int n; // 线段个数
int tx, ty; // 待求点坐标

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// (tx, ty)与(x, y)是否有交点
bool have_point(int x, int y) {
    if (double(ty) >= double(y) * double(x - tx) / double(x)) {
        return true;
    }
    return false;
}

// 两两分组，例如 a, b, c, d => (a, b), (b, c), (c, d)
int binary_search(int n, int *x, int *y) {
    int low = 0, high = n, middle = 0;
    while (low < high) {
        middle = (low + high) / 2;
        if (have_point(x[middle], y[middle]) && !have_point(x[middle + 1], y[middle + 1])) {
            return middle + 1;
        }
        else if (!have_point(x[middle], y[middle])) {
            high = middle;
        }
        else if (have_point(x[middle + 1], y[middle + 1])) {
            low = middle + 1;
        }
    }
    return -1;
}

int main() {
    cin >> n;
    int *x = new int[n];
    int *y = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }
    qsort(x, n, sizeof(int), cmpfunc);
    qsort(y, n, sizeof(int), cmpfunc);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> tx >> ty;
        if (n == 1) {
            if (have_point(x[0], y[0])) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }
        }
        else if (!have_point(x[0], y[0])) {
            printf("%d\n", 0);
        }
        else if (have_point(x[n - 1], y[n - 1])) {
            printf("%d\n", n);
        }
        else {
            int res = binary_search(n - 1, x, y);
            printf("%d\n", res);
        }
    }
    delete[] x;
    delete[] y;
}