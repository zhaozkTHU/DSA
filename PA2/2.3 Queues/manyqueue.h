class Vector {
protected:
    int _size; int _capacity; unsigned int *_elem;
    void copyFrom(const unsigned int *A, int lo, int hi);
    void expand();
    void shrink();
public:
    Vector();
    ~Vector();
    int size() const;
    bool empty() const;
    unsigned int &operator[] (int);
    void push_back(unsigned int);
    unsigned int pop_back();
};

class Queue {
    Vector top, bottom;
public:
    Queue();
    ~Queue();
    void push(unsigned int);
    void pop();
    unsigned int query(unsigned int);
};

class QueueManager {
public:
    QueueManager(unsigned int m);
    void push(unsigned int k, unsigned int x);
    void pop(unsigned int k);
    unsigned int query(unsigned int k, unsigned int i);
    ~QueueManager();
private:
    Queue *Q;
};
