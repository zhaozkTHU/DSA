#include <iostream>
using namespace std;

struct Point {
    int x[5];
    Point() : x{ 0, 0, 0, 0, 0 } {}
};
int d, n;

int main() {
    scanf("%d%d", &d, &n);
    Point *points = new Point[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%d", &points[i].x[j]);
        }
    }
}