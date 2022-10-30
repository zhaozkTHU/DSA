#include <iostream>
#include <sstream>
#define print_error() printf("Error in line %d\n", __LINE__); exit(1);
#define DEFAULT_CAPACITY 3
using namespace std;

template <typename T>
class Vector {
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
    Vector() : _size(0), _capacity(DEFAULT_CAPACITY) {
        _elem = new T[DEFAULT_CAPACITY];
    }
    ~Vector() {
        delete[] _elem;
    }
    int size() const { return _size; }
    bool empty() const { return _size == 0; }
    T &operator[] (int r) {
        if (r >= _size || r < 0) print_error();
        return _elem[r];
    }
    void push_back(T r) {
        expand();
        _elem[_size++] = move(r);
    }
    T pop_back() {
        T e = _elem[--_size];
        shrink();
        return e;
    }
};

struct TreeNode;

struct ChildListNode {
    TreeNode *value;
    ChildListNode *pred, *succ;
    ChildListNode() : value(nullptr), pred(nullptr), succ(nullptr) {}
};

struct TreeNode {
    int value, size, height;
    TreeNode *parent;
    ChildListNode *child_position;
    ChildListNode *header, *trailer;
    TreeNode() : value(), size(), height(), parent(nullptr),
        child_position(nullptr), header(new ChildListNode), trailer(new ChildListNode) {}
    int calcu_size() {
        if (size != 0) return size;
        size = 1;
        for (ChildListNode *p = header->succ; p != trailer; p = p->succ) {
            size += p->value->calcu_size();
        }
        return size;
    }
    int calcu_height() {
        if (calcu_height != 0) return height;
        height = 1;
        int max_height = 0;
        for (ChildListNode *p = header->succ; p != trailer; p = p->succ) {
            max_height = max(max_height, p->value->calcu_height());
        }
        height += max_height;
        return height;
    }
};

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    TreeNode *tree = new TreeNode[N]();
    for (int i = 0; i < N; i++) {
        TreeNode &parent = tree[i];
        parent.value = i + 1;
        parent.header->succ = parent.trailer;
        parent.trailer->pred = parent.header;
        int childnum;
        scanf("%d", &childnum);
        while (childnum--) {
            int child;
            scanf("%d", &child);
            tree[child - 1].parent = &parent;
            ChildListNode *tmp = new ChildListNode;
            tree[child - 1].child_position = tmp;
            tmp->value = &tree[child - 1]; tmp->pred = parent.trailer->pred; tmp->succ = parent.trailer;
            parent.trailer->pred->succ = tmp; parent.trailer->pred = tmp;
        }
    }
    while (M--) {
        int flag;
        scanf("%d", &flag);
        // 子树移动操作
        if (flag == 0) {
            // 读取源子树位置
            string a;
            getline(cin, a);
            istringstream str(a);
            Vector<int> path;
            int word;
            while (str >> word) path.push_back(word);
            TreeNode *p = &tree[0];
            for (int i = 0; i < path.size(); i++) {
                ChildListNode *res = p->header;
                bool valid = true;
                for (int j = 0; j <= i; j++) {
                    res = res->succ;
                    if (res->value == nullptr) {
                        valid = false;
                        break;
                    }
                }
                if (valid == false) break;
                p = res->value;
            }
            TreeNode &src = *p;
            // 读取目标位置
            getline(cin, a);
            istringstream str(a);
            Vector<int> path;
            while (str >> word) path.push_back(word);
            p = &tree[0];
            for (int i = 0; i < path.size(); i++) {
                ChildListNode *res = p->header;
                bool valid = true;
                for (int j = 0; j <= i; j++) {
                    res = res->succ;
                    if (res->value == nullptr) {
                        valid = false;
                        break;
                    }
                }
                if (valid == false) break;
                p = res->value;
            }
            TreeNode &pos = *p;
            // 读取rank
            int rank; cin >> rank;
            // 从源树中移除此节点
            src.child_position->pred->succ = src.child_position->succ;
            src.child_position->succ->pred = src.child_position->pred;
            // 在目标位置的子节点插入节点
            ChildListNode *tmp = pos.header;
            for (int i = 0; i < rank; i++) {
                tmp = tmp->succ;
            }
            ChildListNode *res = new ChildListNode;
            src.child_position = res;
            res->value = &src;
            res->pred = tmp; res->succ = tmp->succ;
            tmp->succ->pred = res; tmp->succ = res;
        }
        // 子树查询操作
        else if (flag == 1) {

        }
        else if (flag == 3) {

        }
        else print_error();
    }
}