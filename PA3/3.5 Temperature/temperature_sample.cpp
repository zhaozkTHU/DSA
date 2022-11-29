#include <cstdlib>
#include <iostream>
#include "temperature.h"

using namespace std;

struct KDNode {
    int temperature, highest_temperature, lowest_temperature;
    int rec_up, rec_down, rec_left, rec_right;
    KDNode() : temperature(0), highest_temperature(0), lowest_temperature(0),
        rec_up(0), rec_down(0), rec_left(0), rec_right(0) {}
};

struct Point {
    int x, y, t;
};

int cmpx(const void *a, const void *b) {
    auto _a = (Point *)a;
    auto _b = (Point *)b;
    return _a->x - _b->x;
}

int cmpy(const void *a, const void *b) {
    auto _a = (Point *)a;
    auto _b = (Point *)b;
    return _a->y - _b->y;
}

void init(int n, const int *x, const int *y, const int *t) {
    Point *points = new Point[n];
    for (int i = 0; i < n; i++) {
        points[i] = { x[i], y[i], t[i] };
    }
}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax) {
    *tmin = rand();
    *tmax = rand();
}
