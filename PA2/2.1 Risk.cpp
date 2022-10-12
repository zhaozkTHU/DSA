#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node *pred, *succ;
    Node(int value = 0, Node *pred = nullptr, Node *succ = nullptr)
        : value(value), pred(pred), succ(succ) {};
    ~Node() = default;
};

class Queue {
private:
    Node *header, *trailer;
    int _size;
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
    int back() {
        if (empty()) { exit(1); }
        return trailer->pred->value;
    }
    /// @brief 队尾添加元素
    /// @param e 添加元素的值
    void push(const int &e) {
        Node *tmp = new Node(e);
        tmp->succ = trailer; tmp->pred = trailer->pred;
        trailer->pred->succ = tmp; trailer->pred = tmp;
        _size++;
    }
    /// @brief 队首元素
    /// @return 队首元素的值
    int front() {
        if (empty()) { exit(1); }
        return header->succ->value;
    }
    /// @brief 弹出队首元素
    /// @return 队首元素的值
    int pop_front() {
        if (empty()) { exit(1); }
        int res = front();
        Node *new_start = header->succ->succ;
        delete header->succ;
        header->succ = new_start;
        new_start->pred = header;
        _size--;
        return res;
    }
    int pop_back() {
        if (empty()) { exit(1); }
        int res = back();
        Node *new_end = trailer->pred->pred;
        delete trailer->pred;
        trailer->pred = new_end;
        new_end->succ = trailer;
        _size--;
        return res;
    }
};

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int binSearch(int *s, const int &e, int lo, int hi) {
    while (lo < hi) {
        int mi = (lo + hi) / 2;
        e < s[mi] ? hi = mi : lo = mi + 1;
    }
    return lo - 1;
}

int main() {
    int n;
    cin >> n;
    int *x = new int[n];
    int *m = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> m[i];
    }
    int T;
    cin >> T;
    int *p = new int[T];
    int *q = new int[T];
    for (int i = 0; i < T; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < T; i++) {
        cin >> q[i];
    }

    int start = 0;
    Queue que;
    int *d = new int[n];
    d[0] = 0;
    d[1] = x[0];
    que.push(x[0]);
    for (int i = 2; i < n; i++) {
        int new_start = max(0, i - m[i]);
        for (int j = start; j < new_start; j++) {
            if (!que.empty() && que.front() == x[j]) {
                que.pop_front();
            }
        }

        while (true) {
            if (que.empty()) {
                que.push(x[i - 1]);
                break;
            }
            if (que.back() >= x[i - 1]) {
                que.push(x[i - 1]);
                break;
            }
            que.pop_back();
        }

        d[i] = que.front();
        start = new_start;
    }

    qsort(d, n, sizeof(int), cmp);

    for (int i = 0; i < n; i++) {
        cout << d[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < T; i++) {
        int low_risk = binSearch(d, p[i] - 1, 0, n) + 1;
        int mid_risk = binSearch(d, q[i] - 1, 0, n) + 1 - low_risk;
        cout << low_risk << " " << mid_risk << endl;
    }
}