#include "kth.h"
#include <iostream>
#define  DEFAULT_CAPACITY 3
#define  Parent(i)         ( ( ( i ) - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Smaller(PQ, i ,j) (PQ[i] < PQ[j] ? i : j)
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
            ( RChildValid(n, i) ? Smaller( PQ, Smaller( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Smaller( PQ, i, LChild(i) ) : i \
            ) \
            ) //相等时父节点优先，如此可避免不必要的交换
using namespace std;

template <typename T>
int percolateUp(T *A, int i) {
	while (0 < i) {
		int j = Parent(i);
		if (A[j] < A[i]) break;
		T tmp = A[i]; A[i] = A[j]; A[j] = tmp;
		i = j;
	}
	return i;
}

template <typename T>
int percolateDown(T *A, int n, int i) {
	int j;
	while (i != (j = ProperParent(A, n, i))) {
		T tmp = A[i]; A[i] = A[j]; A[j] = tmp;
		i = j;
	}
	return i;
}

template <typename T>
class PQ {
	int _size; int _capacity; T *_elem;
	void copyFrom(const T *A, int lo, int hi) {
		_elem = new T[_capacity = (DEFAULT_CAPACITY < 2 * (hi - lo)) ? 2 * (hi - lo) : DEFAULT_CAPACITY];
		for (_size = 0; lo < hi; _size++, lo++)
			_elem[_size] = A[lo];
	}
	void expand() {
		if (_size < _capacity) return;
		if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
		T *oldElem = _elem; _elem = new T[_capacity <<= 1];
		for (int i = 0; i < _size; i++)
			_elem[i] = oldElem[i];
		delete[] oldElem;
	}
	void shrink() {
		if (_capacity < DEFAULT_CAPACITY << 1) return;
		if (_size << 2 > _capacity) return;
		T *oldElem = _elem; _elem = new T[_capacity >>= 1];
		for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
		delete[] oldElem;
	}
public:
	PQ() : _size(0), _capacity(DEFAULT_CAPACITY) {
		_elem = new T[DEFAULT_CAPACITY];
	}
	~PQ() {
		delete[] _elem;
	}
	int size() const { return _size; }
	bool empty() const { return _size == 0; }
	T &operator[] (int r) {
		return _elem[r];
	}
	void push_back(T r) {
		expand();
		_elem[_size++] = move(r);
		percolateUp<T>(_elem, _size - 1);
	}
	T pop_back() {
		T e = _elem[--_size];
		shrink();
		return e;
	}
	T delMax() {
		T res = _elem[0];
		_elem[0] = _elem[--_size];
		percolateDown(_elem, _size, 0);
		return res;
	}
};

struct A {
	int index;
	bool operator<(const A &other) {
		return compare(index, 1, 1, other.index, 1, 1);
	}
};
int cmpa(const void *a, const void *b) {
	auto _a = (A *)a;
	auto _b = (A *)b;
	return !(*_a < *_b);
}

struct B {
	int index;
	bool operator<(const B &other) {
		return compare(1, index, 1, 1, other.index, 1);
	}
};
int cmpb(const void *a, const void *b) {
	auto _a = (B *)a;
	auto _b = (B *)b;
	return !(*_a < *_b);
}

struct C {
	int index;
	bool operator<(const C &other) {
		return compare(1, 1, index, 1, 1, other.index);
	}
};
int cmpc(const void *a, const void *b) {
	auto _a = (C *)a;
	auto _b = (C *)b;
	return !(*_a < *_b);
}

A *a;
B *b;
C *c;

struct ABC {
	int x, y, z;
	bool operator<(const ABC &other) {
		return compare(a[x].index, b[y].index, c[z].index, a[other.x].index, b[other.y].index, c[other.z].index);
	}
};

void get_kth(int n, int k, int *x, int *y, int *z) {
	a = new A[n];
	b = new B[n];
	c = new C[n];
	for (int i = 0; i < n; i++) {
		a[i].index = i + 1;
		b[i].index = i + 1;
		c[i].index = i + 1;
	}
	qsort(a, n, sizeof(A), cmpa);
	qsort(b, n, sizeof(B), cmpb);
	qsort(c, n, sizeof(C), cmpc);
	PQ<ABC> res;
	res.push_back(ABC{ 0, 0 ,0 });
	for (int i = 1; i < k; i++) {
		// for (int j = 0; j < res.size(); j++) {
		// 	printf("%d %d %d\n", res[j].x, res[j].y, res[j].z);
		// }
		// printf("\n");
		// printf("%d %d %d\n", a[res[0].x].index, b[res[0].y].index, c[res[0].z].index);
		// printf("%d %d %d\n", res[0].x, res[0].y, res[0].z);
		auto tmp = res.delMax();
		if (tmp.y == 0 && tmp.z == 0) {
			if (tmp.x < n - 1)
				res.push_back(ABC{ tmp.x + 1, tmp.y, tmp.z });
			if (tmp.y < n - 1)
				res.push_back(ABC{ tmp.x, tmp.y + 1, tmp.z });
			if (tmp.z < n - 1)
				res.push_back(ABC{ tmp.x, tmp.y, tmp.z + 1 });
		}
		else if (tmp.z == 0) {
			if (tmp.y < n - 1)
				res.push_back(ABC{ tmp.x, tmp.y + 1, tmp.z });
			if (tmp.z < n - 1)
				res.push_back(ABC{ tmp.x, tmp.y, tmp.z + 1 });
		}
		else {
			if (tmp.z < n - 1)
				res.push_back(ABC{ tmp.x, tmp.y, tmp.z + 1 });
		}
	}
	*x = a[res[0].x].index;
	*y = b[res[0].y].index;
	*z = c[res[0].z].index;

	return;
}