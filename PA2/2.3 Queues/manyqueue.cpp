#include"manyqueue.h"
#include <cstdlib>
#define DEFAULT_CAPACITY 3

void Vector::copyFrom(const unsigned int *A, int lo, int hi) {
    _elem = new unsigned int[_capacity = (DEFAULT_CAPACITY < 2 * (hi - lo)) ? 2 * (hi - lo) : DEFAULT_CAPACITY];
    for (_size = 0; lo < hi; _size++, lo++)
        _elem[_size] = A[lo];
}

void Vector::expand() {
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    unsigned int *oldElem = _elem; _elem = new unsigned int[_capacity <<= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

void Vector::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return;
    unsigned *oldElem = _elem; _elem = new unsigned int[_capacity >>= 1];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete[] oldElem;
}

Vector::Vector() : _size(0), _capacity(DEFAULT_CAPACITY){
    _elem = new unsigned int[DEFAULT_CAPACITY];
}

Vector::~Vector() {
    delete[] _elem;
}

int Vector::size() const { return _size; }

bool Vector::empty() const { return _size == 0; }

unsigned int &Vector::operator[] (int r) {
    if (r >= _size || r < 0) exit(1);
    return _elem[r];
}

void Vector::push_back(unsigned int r) {
    expand();
    _elem[_size++] = r;
}

unsigned int Vector::pop_back() {
    unsigned int e = _elem[--_size];
    shrink();
    return e;
}

Queue::Queue() = default;

Queue::~Queue() = default;

void Queue::push(unsigned int a) {
    bottom.push_back(a);
}

void Queue::pop() {
    if (top.empty()) {
        int tmp = bottom.size();
        for (int i = 0; i < tmp; i++)
            top.push_back(bottom.pop_back());
    }
    if (top.empty()) return;
    top.pop_back();
}

unsigned int Queue::query(unsigned int i) {
    if (bottom.empty() && top.empty()) return 0;
    if (i <= top.size()) return top[top.size() - i];
    if (i <= bottom.size() + top.size()) return bottom[i - top.size() - 1];
    if (!bottom.empty()) {
        return bottom[bottom.size() - 1];
    }
    else {
        return top[0];
    }
}

QueueManager::QueueManager(unsigned int m) {
    Q = new Queue[m]();
}
QueueManager::~QueueManager() {
    delete[] Q;
}
void QueueManager::push(unsigned int k, unsigned int x) {
    Q[k - 1].push(x);
}
void QueueManager::pop(unsigned int k) {
    Q[k - 1].pop();
}
unsigned int QueueManager::query(unsigned int k, unsigned int i) {
    return Q[k - 1].query(i);
}