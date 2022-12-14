#include "sort.h"
#include <iostream>
#include <memory.h>

bool compare(int x, int y) {
	int max, min;
	compare(x, y, y, &max, &min);
	return max == y;
}

inline void swap(int &a, int &b) {
	int t = a;
	a = b, b = t;
}

int cmp = 0;

void quick_sort(int left, int right, int *a, int limit) {
	if (left >= right) return;
	int max, min;
	int *tmp = new int[right - left + 1];
	memcpy(tmp, a + left, sizeof(int) * (right - left + 1));
	int l(left), r(right);
	for (int i = 1; i < right - left + 1; i += 2) {
		if (i == right - left) {
			cmp++;
			if (cmp == limit - 1) exit(cmp);
			if (compare(tmp[0], tmp[i])) {
				a[r--] = tmp[i];
			}
			else {
				a[l++] = tmp[i];
			}
			continue;
		}
		cmp++;
		if (cmp == limit - 1) exit(cmp);
		compare(tmp[0], tmp[i], tmp[i + 1], &max, &min);
		if (min == tmp[0]) {
			a[r--] = tmp[i];
			a[r--] = tmp[i + 1];
		}
		else if (max == tmp[0]) {
			a[l++] = tmp[i];
			a[l++] = tmp[i + 1];
		}
		else if (max == tmp[i]) {
			a[r--] = tmp[i];
			a[l++] = tmp[i + 1];
		}
		else {
			a[l++] = tmp[i];
			a[r--] = tmp[i + 1];
		}
	}
	if (l != r) exit(EXIT_FAILURE);
	a[l] = tmp[0];
	delete[] tmp;
	quick_sort(left, l - 1, a, limit);
	quick_sort(l + 1, right, a, limit);
}

void sort(int n, int limit, int *a) {
	quick_sort(0, n - 1, a, limit);
}
