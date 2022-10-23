#include <iostream>
using namespace std;

class Node {
public:
    long long value;
    Node *pred, *succ;
    Node(long long value = 0, Node *pred = nullptr, Node *succ = nullptr)
        : value(value), pred(pred), succ(succ) {};
    ~Node() = default;
};

class Queue {
private:
    Node *header, *trailer;
    long long _size;
public:
    /// @brief 构造函数
    Queue() : _size(0) {
        header = new Node();
        trailer = new Node();
        header->succ = trailer; trailer->pred = header;
    }
    /// @brief 默认析构函数
    ~Queue() = default;
    /// @brief 队列是否为空
    /// @return bool，空为true
    bool empty() {
        return _size == 0;
    }
    /// @brief 队尾元素
    /// @return 返回队尾元素值
    long long back() {
        if (empty()) { exit(1); }
        return trailer->pred->value;
    }
    /// @brief 队尾添加元素
    /// @param e 添加元素的值
    void push(const long long &e) {
        Node *tmp = new Node(e);
        tmp->succ = trailer; tmp->pred = trailer->pred;
        trailer->pred->succ = tmp; trailer->pred = tmp;
        _size++;
    }
    /// @brief 队首元素
    /// @return 队首元素的值
    long long front() {
        if (empty()) { exit(1); }
        return header->succ->value;
    }
    /// @brief 弹出队首元素
    /// @return 队首元素的值
    long long pop_front() {
        if (empty()) { exit(1); }
        long long res = front();
        Node *new_start = header->succ->succ;
        delete header->succ;
        header->succ = new_start;
        new_start->pred = header;
        _size--;
        return res;
    }
    long long pop_back() {
        if (empty()) { exit(1); }
        long long res = back();
        Node *new_end = trailer->pred->pred;
        delete trailer->pred;
        trailer->pred = new_end;
        new_end->succ = trailer;
        _size--;
        return res;
    }
};

int cmp(const void *a, const void *b) {
    return int(*(long long *)a - *(long long *)b);
}

// 二分查找
long long binSearch(long long *s, const long long &e, long long lo, long long hi) {
    while (lo < hi) {
        long long mi = (lo + hi) / 2;
        e < s[mi] ? hi = mi : lo = mi + 1;
    }
    return lo - 1;
}

int main() {
    long long n;
    scanf("%lld", &n);
    long long *x = new long long[n];
    long long *m = new long long[n];
    for (long long i = 0; i < n; i++) {
        scanf("%lld", &x[i]);
    }
    for (long long i = 0; i < n; i++) {
        scanf("%lld", &m[i]);
    }
    long long T;
    cin >> T;
    long long *p = new long long[T];
    long long *q = new long long[T];
    for (long long i = 0; i < T; i++) {
        scanf("%lld%lld", &p[i], &q[i]);
    }

    long long start = 0;
    Queue que;
    long long *d = new long long[n];
    d[0] = 0;
    d[1] = x[0];
    que.push(x[0]);
    for (long long i = 2; i < n; i++) {
        long long new_start = max((long long)(0), i - m[i]); //区间的新起点

        // 将起点前的结点删去
        for (long long j = start; j < new_start; j++) {
            if (!que.empty() && que.front() == x[j]) {
                que.pop_front();
            }
        }

        // queap队列操作
        while (true) {
            // 队列为空直接添加
            if (que.empty()) {
                que.push(x[i - 1]);
                break;
            }
            // 队尾大于等于新添加的直接添加
            if (que.back() >= x[i - 1]) {
                que.push(x[i - 1]);
                break;
            }
            // 队尾小于，删去
            que.pop_back();
        }

        d[i] = que.front(); // 队首即为正确答案
        start = new_start;
    }

    // 对d[i]排序以便二分查找
    qsort(d, n, sizeof(long long), cmp);

    for (long long i = 0; i < T; i++) {
        long long low_risk = binSearch(d, p[i] - 1, 0, n) + 1;
        long long mid_risk = binSearch(d, q[i] - 1, 0, n) + 1 - low_risk;
        printf("%lld %lld\n", low_risk, mid_risk);
    }
}