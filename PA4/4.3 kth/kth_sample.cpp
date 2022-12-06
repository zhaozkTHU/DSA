#include "kth.h"
#include <bits/stdc++.h>
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
#define DEFAULT_CAPACITY 3
using namespace std;
using Rank = int;

template <typename T>
class Vector {
public:
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
	Vector() : _size(0), _capacity(DEFAULT_CAPACITY) {
		_elem = new T[DEFAULT_CAPACITY];
	}
	Vector(int n) : _size(n), _capacity(n), _elem(new T[n]) {}
	~Vector() {
		delete[] _elem;
	}
	int size() const { return _size; }
	bool empty() const { return _size == 0; }
	T &operator[] (int r) {
		if (r >= _size || r < 0) print_error(__LINE__);
		return _elem[r];
	}
	virtual void push_back(T r) {
		expand();
		_elem[_size++] = move(r);
	}
	T pop_back() {
		T e = _elem[--_size];
		shrink();
		return e;
	}
};

template <typename T>
class PQ : public Vector<T> {
	int perlocateUp(T *A, int i) {
		while (0 < i) {
			int j = Parent(i);
		}
	}
public:
	PQ(int n) : Vector<T>::Vector<T>(int n) {}
	void push_back(T e) override {
		Vector<T>::push_back(e);
	}
	T delMin() {
		T minElem = _elem[0];
		_elem[0] = _elem[--size];
		percolateDown(_elem, size, 0);
	}
	Rank percolateDown(T *A, Rank n, Rank i) {
		Rank j;
		while (i != (j = ProperParent(A, n, i))) {
			auto tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			i = j;
		}
		return i;
	}
	void heapify(T *A, Rank n) {
		for (Rank i = n >> 1 - 1; 0 <= i; i--) {
			percolateDown(A, n, i);
		}
	}
};

struct A {
	int index;
	bool operator<(const A &other) {
		return compare(index, 1, 1, other.index, 1, 1);
	}
};

struct B {
	int index;
	bool operator<(const B &other) {
		return compare(1, index, 1, 1, other.index, 1);
	}
};

struct C {
	int index;
	bool operator<(const C &other) {
		return compare(1, 1, index, 1, 1, other.index);
	}
};

void get_kth(int n, int k, int *x, int *y, int *z) {
	PQ<A> a(n);
	PQ<B> b(n);
	PQ<C> c(n);
	for (int i = 1; i <= n; i++) {
		a[i - 1] = A{ i };
		b[i - 1] = B{ i };
		c[i - 1] = C{ i };
	}
	a.heapify(a._elem, a._size);
	b.heapify(b._elem, b._size);
}